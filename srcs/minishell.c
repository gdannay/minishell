/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:29:13 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/17 17:02:17 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_env(char ***env)
{
	int i;

	i = -1;
	if (env && *env)
	{
		while ((*env)[++i])
			ft_strdel(&(*env)[i]);
		free(*env);
		*env = NULL;
	}
}

static char		**new_com(char *first, char *second)
{
	char	**com;

	if ((com = (char **)malloc(sizeof(char *) * 3)) == NULL
			|| !(com[0] = ft_strdup(first))
			|| !(com[1] = ft_strdup(second)))
		return (NULL);
	com[2] = 0;
	return (com);
}

static int		add_shlvl(char ***env)
{
	int		i;
	char	*value;
	char	**com;

	i = 0;
	while ((*env) && (*env)[i] && ft_strncmp((*env)[i], "PWD", 3))
		i++;
	if (!(*env)[i] && (com = new_com("cd", ".")) && !exec_com(com, env))
		free_env(&com);
	i = 0;
	while ((*env) && (*env)[i] && ft_strncmp((*env)[i], "SHLVL", 5))
		i++;
	if ((*env) && (*env)[i])
		value = ft_itoa(ft_atoi((*env)[i] + 6) + 1);
	else
		value = ft_strdup("1");
	if (!value || (com = new_com("SHLVL", value)) == NULL
		|| ft_setenv(com, env))
		return (1);
	ft_strdel(&value);
	free_env(&com);
	return (0);
}

static int		loop(char **input, int *exit, char ***env)
{
	char		**com;
	static char	*tmp = NULL;
	static char	open = 0;
	int			ret;

	ret = 0;
	if ((ret = echap(&tmp, input, &open)) != 0)
		return (ret);
	if ((com = ft_strsplitspace(tmp)) == NULL
		|| !(com = manage_home(com, env)))
		return (1);
	if (!(ft_strncmp(com[0], "exit", 4)) && com[1] && com[2])
		write(2, "exit: too many arguments\n", 25);
	else if (!(ft_strncmp(com[0], "exit", 4)))
		*exit = 0;
	else if (tmp && exec_com(com, env))
		return (1);
	if (*exit)
		ft_printf("$> ");
	if (!(*exit) && com[1])
		ret = ft_atoi(com[1]);
	ft_strdel(&tmp);
	free_env(&com);
	return (ret);
}

int				main(int ac, char **av, char **env)
{
	int		exit;
	char	**cpy;
	char	*input;
	int		ret;

	(void)ac;
	(void)av;
	cpy = NULL;
	input = NULL;
	ret = 0;
	if (((cpy = ft_tabdup(env)) == NULL
				|| add_shlvl(&cpy)))
		return (1);
	exit = 1;
	ft_printf("$> ");
	while (exit && get_next_line(0, &input))
	{
		ret = loop(&input, &exit, &cpy);
		if (ret == 1 && exit)
			return (1);
	}
	ft_strdel(&input);
	free_env(&cpy);
	ft_printf("exit\n");
	return (ret);
}
