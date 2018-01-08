/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:29:13 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/08 13:38:02 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_env(char ***env)
{
	int i;

	i = -1;
	if (env && *env)
	{
		while ((*env)[++i])
			ft_strdel(&(*env)[i]);
		free(env);
		env = NULL
	}
}

static int	loop(char **input, int *exit, char ***env)
{
	char **com;

	if ((com = ft_strsplit(input, ' ')) == NULL)
		return (1);
	if (input && *input && !(ft_strcmp(*input, "exit")))
		*exit = 0;
	else if (input && *input && exec_com(&com, env))
		return (1);
	if (*exit)
		ft_printf("$> ");
	ft_strdel(input);
	return (0);
}

int			main(int ac, char **av, char **env)
{
	int		exit;
	char	**cpy;
	char	*input;

	(void)ac;
	(void)av;
	input = NULL;
	if ((cpy = ft_dstrdup(env)) == NULL)
		return (1);
	exit = 1;
	ft_printf("$> ");
	while (exit && get_next_line(0, &input))
	{
		if (loop(&input, &exit, &cpy))
			return (1);
	}
	ft_strdel(&input);
	free_env(&cpy);
	if (exit)
		ft_printf("exit\n");
	return (0);
}
