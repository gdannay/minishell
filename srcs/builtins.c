/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 13:06:37 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/17 16:58:23 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				search_env(char ***env, char *var, size_t length)
{
	int	i;

	i = 0;
	if (!env || !(*env))
		return (0);
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
		}
		else if (com[i + 1] && !ft_strstr(com[i], "$"))
			ft_printf("%s ", com[i]);
		else
			ft_printf("%s", com[i]);
	}
	ft_printf("\n");
	return (0);
}

static void		replace_env(char **str, char ***env, int i)
{
	ft_strdel(&(*env)[i]);
	(*env)[i] = *str;
}

static int		set_dir(char *new, char ***env, char *old)
{
	char	*pwd;
	char	*opwd;
	int		j;
	int		i;

	j = search_env(env, "OLDPWD", 6);
	i = search_env(env, "PWD", 3);
	if ((pwd = ft_strjoin("PWD=", new)) == NULL
		|| (opwd = ft_strjoin("OLDPWD=", old)) == NULL)
		return (1);
	if ((*env)[i])
		replace_env(&pwd, env, i);
	else
		(*env) = add_env(env, &pwd);
	if ((*env)[j])
		replace_env(&opwd, env, j);
	else
		(*env) = add_env(env, &opwd);
	return (0);
}

int				ft_cd(char **com, char ***env)
{
	char	old[BUFF_SIZE];
	char	new[BUFF_SIZE];
	char	*home;

	home = NULL;
	if (!(env) || !(*env))
		return (0);
	if (com[0] && com[1])
		return (error_many_arguments("cd"));
	if ((!com[0] && !(home = get_home(com[0], env))))
		return (0);
	if (getcwd(old, BUFF_SIZE) == NULL)
		return (1);
	if (home && chdir(home) == -1)
	{
		ft_strdel(&home);
		return (ft_cd_error(com));
	}
	else if (!home && chdir(com[0]) == -1)
		return (ft_cd_error(com));
	if (getcwd(new, BUFF_SIZE) == NULL)
		return (1);
	ft_strdel(&home);
	return (set_dir(new, env, old));
}
