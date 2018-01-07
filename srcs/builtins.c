/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 13:06:37 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/07 17:41:48 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **com, char ***env)
{
	int i;

	i = 0;
	(void)env;
	while (com && com[++i])
	{
		if (com[i + 1])
			ft_printf("%s ", com[i]);
		else
			ft_printf("%s\n", com[i]);
	}
	return (0);
}

static int	ft_cd_error(char **com)
{
	ft_printf("minishell: cd: %s: ", com[1]);
	write(2,"No such file or directory\n", 26);
	return (0);
}

static int	set_dir(char *path, char ***env, int i, int free)
{
	char	*pwd;
	int		ret;

	(void)env;
	(void)i;
	pwd = NULL;
	ret = 0;
	if ((pwd = ft_strjoin("PWD=", path)) == NULL
		|| chdir(path) == -1)
		ret = 1;
	if ((*env)[i])
		ft_strdel(&(*env)[i]);
		(*env)[i] = pwd;
	else
		(*env) = add_env(env, &pwd);
	if (free)
		ft_strdel(&path);
	return (ret);
}

static char		*manage_path(char *path, char *name)
{
	int i;
	int j;

	i = -1;
	j = 0;
	if (!(ft_strcmp(name, ".")))
		return (ft_strdup(path));
	else if (!(ft_strcmp(name, "..")))
	{
		while (path[++i])
		{
			if (path[i] == '/')
				j = i;
		}
		if (j == 0)
			return (ft_strdup("/"));
		else
			return (ft_strndup(path, j));
	}
	return (ft_joinpath(path, name));
}

int		ft_cd(char **com, char ***env)
{
	int		i;
	char	buff[BUFF_SIZE];
	char	*path;
	DIR		*rep;

	i = 0;
	(void)com;
	path = NULL;
	if (!(env) || !(*env))
		return (1);
	if (!(com[1]))
		return (0);
	while ((*env)[i] && ft_strncmp((*env)[i], "PWD", 3))
		i++;
	if (getcwd(buff, BUFF_SIZE) == NULL
			|| (path = manage_path(buff, com[1])) == NULL)
		return (1);
	if ((rep = opendir(path)) == NULL)
		ft_strdel(&path);
	if (!(rep) && (rep = opendir(com[1])) == NULL)
		return (ft_cd_error(com));
	if (rep && closedir(rep) == -1)
		return (1);
	return (path ? set_dir(path, env, i, 1) : 
				set_dir(buff, env, i, 0));
}
