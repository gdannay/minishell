/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:18:48 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/11 20:22:11 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		last_slash(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '/')
			j = i;
		i++;
	}
	return (j);
}

char			*manage_path(char *str, char **rest)
{
	int		j;
	char	*path;

	j = last_slash(str);
	if (str == NULL || rest == NULL)
		return (NULL);
	if (str[j] == '/')
	{
		if (j == 0 && !(path = ft_strdup("/")))
			return (NULL);
		else if (j > 0 && (path = ft_strndup(str, j)) == NULL)
			return (NULL);
		j++;
		if ((*rest = ft_strsub(str, j, ft_strlen(str) - (size_t)j)) == NULL)
			return (NULL);
		return (path);
	}
	if ((*rest = ft_strdup(str)) == NULL)
		return (NULL);
	return (ft_strdup("."));
}

static char		*parent(char *path, char *name, char ***com, char ***env)
{
	char	*spec;
	char	*tmp;
	int		j;

	j = last_slash(path);
	if (j == 0)
		spec = ft_strdup("/");
	else
		spec = ft_strndup(path, j);
	if (name[2] && name[3] && name[2] == '/')
	{
		tmp = *com[0];
		(*com)[0] = (*com)[0] + 3;
		if (chdir(spec) == -1)
			return (NULL);
		ft_strdel(&spec);
		ft_cd(*com, env);
		(*com)[0] = tmp;
		return ("./");
	}
	return (spec);
}

static char		*actual_dir(char *path, char *name, char ***com, char ***env)
{
	char	*tmp;

	tmp = NULL;
	if (name[1] && name[2] && name[1] == '/')
	{
		tmp = *com[0];
		(*com)[0] = (*com)[0] + 2;
		ft_cd(*com, env);
		(*com)[0] = tmp;
		return ("./");
	}
	else
		return (ft_strdup(path));
}

char			*manage_dir(char *path, char *name, char ***com, char ***env)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!(ft_strncmp(name, "/", 1)))
		return (ft_strdup(name));
	else if (!(ft_strncmp(name, "..", 2)))
		return (parent(path, name, com, env));
	else if (!(ft_strncmp(name, ".", 1)))
		return (actual_dir(path, name, com, env));
	else if (!(ft_strncmp("~", name, 1)) || !name)
	{
		i = 0;
		while ((*env) && (*env)[i] && ft_strncmp(((*env)[i]), "HOME", 4))
			i++;
		if (!(*env) || !(*env)[i])
			write(2, "No $home variable set.\n", 23);
		else if (!name)
			return (ft_strdup((*env)[i] + 5));
		else
			return (ft_strjoin((*env)[i] + 5, name + 1));
		return ("./");
	}
	return (ft_joinpath(path, name));
}
