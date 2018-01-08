/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 17:02:27 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/08 13:47:53 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	flag_error(char c, char ***env, char ***com)
{
	free_env(env);
	ft_printf("env: illegal option -- %c\n", c);
	write(2, "usage: env [-i] [-u name] [name=value ...]
			[utility [argument...]]\n", 68);
	(*com) = (*com + i);
	return (0);
}

static int	exec_env(char ***com, char ***env, int *i, int *exit)
{
	int j;

	while ((*com)[*i] && (*com)[*i][0] == '-')
	{
		j = 0;
		while ((*com)[*i][++j])
		{
			if ((*com)[*i][j] == 'u' && ft_unsetenv(com + *i + 1, env))
				return (1);
			else if ((*com)[*i][j] == 'i')
				free_env(env);
			else
				return (flag_error((*com)[*i][j], env, com));
		}
		*i = *i + 1;
		ft_strdel
	}
	while (ft_strstr(com[*i], "="))
	{
		ft_setenv(com + *i + 1, env);
		*i = *i + 1;
	}
	if ((exec_com(
}

int		ft_env(char ***com, char ***env)
{
	int		i;
	char	**cpy;
	int		exit;

	i = 0;
	exit = 0;
	if (!((*com)[1]))
	{
		while ((*env)[++i])
			ft_printf("%s\n", (*env)[i]);
	}
	else
	{
		if ((cpy = ft_dstrdup(*env)) == NULL)
			return (1);
		while (exit && (*com)[++i])
		{
			if (exec_env(com, &cpy, &i, &exit))
				return (1);
		}
	}
	return (0);
}
