/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_com.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 12:40:06 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/07 17:06:36 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	g_mini_command[] =
{
	{"echo", &ft_echo},
	{"cd", &ft_cd},
	{"setenv", &ft_setenv},
	{"unsetenv", &ft_unsetenv},
	{"env", &ft_env},
};

int		exec_com(char *input, char ***env)
{
	int 	i;
	int		ret;
	char	**com;

	i = 0;
	ret = 0;
	com = NULL;
	if ((com = ft_strsplit(input, ' ')) == NULL)
		return (1);
	while (i < 5 && ft_strcmp(com[0], g_mini_command[i].name))
		i++;
	if (i < 5)
		ret = g_mini_command[i].com(com, env);
	i = -1;
	while (com[++i])
		ft_strdel(&com[i]);
	free(com);
	return (ret);
}
