/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 17:02:27 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/11 19:13:10 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		flag_error(char c, char ***env, char ***com, int i)
{
	free_env(env);
	ft_printf("env: illegal option -- %c\n", c);
	write(2, "usage: env [-i] [-u name] [name=value ...]", 42);
	write(2, " [utility [argument...]]\n", 25);
	(*com) = *(com + i);
	return (0);
}

static int		check_flag(char **com, char ***env, int *i)
{
	int j;
	int ret;

	j = 0;
	ret = 0;
	while (com[*i][++j])
	{
		if (com[*i][j] == 'u' && com[*i + 1]
				&& !(ret = ft_unsetenv(com + *i + 1, env)))
		{
			*i = *i + 1;
			break ;
		}
		else if (ret)
			return (1);
		else if (com[*i][j] == 'i')
			free_env(env);
		else if (!(com[*i + 1]))
			return (flag_error(com[*i][j], env, &com, *i));
	}
	return (0);
}

static int		emergency_path(char ***env)
{
	int		i;
	char	**emergency;

	i = 0;
	if (env && (*env))
	{
		while ((*env)[i] && ft_strncmp("PATH", (*env)[i], 4))
			i++;
	}
	if (!(*env) || !((*env)[i]))
	{
		if ((emergency = (char **)malloc(sizeof(char *) * 3)) == NULL)
			return (1);
		emergency[0] = ft_strdup("PATH");
		emergency[1] = ft_strdup("/usr/bin:/bin:/usr/sbin:/sbin");
		emergency[2] = 0;
		if (ft_setenv(emergency, env))
		{
			free_env(&emergency);
			return (1);
		}
		free_env(&emergency);
	}
	return (0);
}

static int		exec_env(char **com, char ***env)
{
	int		i;
	char	**new;
	int		ret;

	i = -1;
	ret = 0;
	while (com[++i] && com[i][0] == '-')
	{
		if (check_flag(com, env, &i))
			return (1);
	}
	i--;
	while (ft_strstr(com[++i], "=")
			&& (new = ft_strsplit(com[i], '='))
			&& !(ret = ft_setenv(new, env)))
		free_env(&new);
	if (ret || (!(com[i]) && ft_env(com + i, env)))
		return (1);
	if (emergency_path(env))
		return (1);
	if (com[i] && (exec_com(com + i, env)))
		return (1);
	free_env(env);
	return (0);
}

int				ft_env(char **com, char ***env)
{
	char	**cpy;
	int		i;

	i = -1;
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
