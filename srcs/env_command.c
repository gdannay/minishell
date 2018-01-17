/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 17:02:27 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/17 15:46:13 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		flag_error(char c)
{
	write(2, "env: illegal option -- ", 23);
	write(2, &c, 1);
	write(2, "\nusage: env [-i] [-u name] [name=value ...]", 43);
	write(2, " [utility [argument...]]\n", 25);
	return (2);
}

static int		check_flag(char **com, char ***env, int *i)
{
	int j;
	int ret;

	j = 0;
	ret = 0;
	if (!(com[*i][1]))
		return (flag_error(com[*i][1]));
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
		else
			return (flag_error(com[*i][j]));
	}
	return (0);
}

static int		emergency_path(char ***env)
{
	int		i;
	char	**emergency;

	i = search_env(env, "PATH", 4);
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
		ft_tabdel(&emergency);
	}
	return (0);
}

static int		exec_env(char **com, char ***env)
{
	int		i;
	char	**new;
	int		ret;

	i = 0;
	ret = 0;
	while (com[i] && com[i][0] == '-' && !(ret = check_flag(com, env, &i)))
		i++;
	if (ret == 1)
		return (1);
	else if (ret == 2)
		return (0);
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
		if ((cpy = ft_tabdup(*env)) == NULL)
			return (1);
		if (exec_env(com, &cpy))
			return (1);
		free_env(&cpy);
	}
	return (0);
}
