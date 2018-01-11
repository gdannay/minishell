/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 19:05:29 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/11 19:33:47 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error_mes(char *str)
{
	write(2, "minishell: command not found: ", 30);
	ft_printf("%s\n", str);
	return (0);
}

int		error_alphanum(void)
{
	write(2, "setenv: Variable name must contain", 34);
	write(2, " alphanumeric characters.\n", 26);
	return (0);
}

int		error_many_arguments(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": Too many arguments.\n", 22);
	return (0);
}

int		ft_cd_error(char **com)
{
	ft_printf("minishell: cd: %s: ", com[0]);
	write(2, "No such file or directory\n", 26);
	return (0);
}
