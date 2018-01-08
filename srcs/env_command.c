/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 17:02:27 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/08 16:39:44 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	flag_error(char c, char ***env, char ***com, int i)
{
	free_env(env);
	ft_printf("env: illegal option -- %c\n", c);
	write(2, "usage: env [-i] [-u name] [name=value ...]", 42);
	write(2, " [utility [argument...]]\n", 25);
	(*com) = *(com + i);
	return (0);
}

static int	exec_env(char **com, char ***env)
{
	int		j;
	int		i;
	char	**new;
	int		ret;

	i = -1;
	ret = 0;
	while (com[++i] && com[i][0] == '-')
	{
		j = 0;
		while (com[i][++j])
		{
			if (com[i][j] == 'u' && ft_unsetenv(com + i + 1, env))
				return (1);
			else if (com[i][j] == 'i')
				free_env(env);
			else
				return (flag_error(com[i][j], env, &com, i));
		}
	}
	i--;
	while (ft_strstr(com[++i], "=")
			&& (new = ft_strsplit(com[i], '='))
			&& !(ret = ft_setenv(new, env)))
		free_env(&new);
	if (ret)
		return (1);
	if (!(com[i]) && ft_env(com + i, env))
		return (1);
	else if (com[i] && (exec_com(com + i, env)))
		return (1);
	free_env(env);
	return (0);
}

int		ft_env(char **com, char ***env)
{
	char	**cpy;
	int		i;

	i = 0;
	if (!(com[0]))
	{
		while (env && *env && (*env)[++i])
			ft_printf("%s\n", (*env)[i]);
	}
	else
	{
		if ((cpy = ft_dstrdup(*env)) == NULL)
			return (1);
		if (exec_env(com, &cpy))
			return (1);
	}
	return (0);
}
