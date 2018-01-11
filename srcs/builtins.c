/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 13:06:37 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/11 20:30:59 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		search_env(char ***env, char *var, size_t length)
{
	int	i;

	i = 0;
	while ((*env)[i] && ft_strncmp((*env)[i], var, length))
		i++;
	return (i);
}

int				ft_echo(char **com, char ***env)
{
	int i;
	int j;
	int k;

	i = -1;
	j = -1;
	k = 0;
	while (com && com[++i])
	{
		if (ft_strstr(com[i], "$"))
		{
			while (com[i][++j] && com[i][j] != '$')
				ft_putchar(com[i][j]);
			k = search_env(env, com[i] + j + 1, ft_strlen(com[i] + j + 1));
			if ((*env)[k])
				ft_printf("%s", (*env)[k] + ft_strlen(com[i]) - j);
			if (!com[i + 1])
				ft_printf("\n");
		}
		else if (com[i + 1] && !ft_strstr(com[i], "$"))
			ft_printf("%s ", com[i]);
		else
			ft_printf("%s\n", com[i]);
	}
	return (0);
}

static void		replace_env(char **str, char ***env, int i)
{
	ft_strdel(&(*env)[i]);
	(*env)[i] = *str;
}

static int		set_dir(char *path, char ***env, int i, char *old)
{
	char	*pwd;
	char	*opwd;
	int		j;

	j = 0;
	if ((pwd = ft_strjoin("PWD=", path)) == NULL
		|| (opwd = ft_strjoin("OLDPWD=", old)) == NULL
		|| chdir(path) == -1)
		return (1);
	if ((*env)[i])
		replace_env(&pwd, env, i);
	else
		(*env) = add_env(env, &pwd);
	while ((*env)[j] && ft_strncmp((*env)[j], "OLDPWD", 6))
		j++;
	if ((*env)[j])
		replace_env(&opwd, env, j);
	else
		(*env) = add_env(env, &opwd);
	ft_strdel(&path);
	ft_strdel(&old);
	return (0);
}

int				ft_cd(char **com, char ***env)
{
	int		i;
	char	buff[BUFF_SIZE];
	char	*path;
	DIR		*rep;
	char	*old;

	if (!(env) || !(*env))
		return (0);
	if (com[0] && com[1])
		return (error_many_arguments("cd"));
	i = search_env(env, "PWD", 3);
	if (getcwd(buff, BUFF_SIZE) == NULL
		|| (path = manage_dir(buff, com[0], &com, env)) == NULL)
		return (1);
	if (!ft_strcmp(path, "./"))
		return (0);
	if ((rep = opendir(path)) == NULL)
		ft_strdel(&path);
	if (!(rep) && (rep = opendir(com[0])) == NULL)
		return (ft_cd_error(com));
	if ((!(path) && !(path = ft_strdup(com[0])))
		|| (rep && closedir(rep) == -1)
		|| (!(old = ((*env)[i] ? ft_strdup((*env)[i] + 4) : ft_strdup(buff)))))
		return (1);
	return (set_dir(path, env, i, old));
}
