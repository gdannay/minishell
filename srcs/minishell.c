/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:29:13 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/07 16:02:37 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	int		exit;
	char	**cpy;
	char	*input;
	int		i;

	i = -1;
	(void)ac;
	(void)av;
	input = NULL;
	if ((cpy = ft_dstrdup(env)) == NULL)
		return (1);
	exit = 1;
	ft_printf("$> ");
	while (exit && get_next_line(0, &input))
	{
	i = -1;
		if (input && !(ft_strcmp(input, "exit")))
			exit = 0;
		else if (input && exec_com(input, &cpy))
			return (1);
		if (exit)
			ft_printf("$> ");
		ft_strdel(&input);
	//	while (cpy[++i])
	//		ft_printf("%s\n", cpy[i]);
	}
	ft_strdel(&input);
	if (exit)	
		ft_printf("exit\n");
	return (0);
}
