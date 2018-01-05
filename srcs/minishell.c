/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:29:13 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/05 18:40:18 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	int i;

	i = 0;
	if (1)
		ac = 1;
	(void)av;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	execve("/bin/ls", av, NULL);
	
	return (0);
}
