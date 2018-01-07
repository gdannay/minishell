/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:46:50 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/07 17:35:59 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# include <dirent.h>
# include "get_next_line.h"

typedef struct		s_command
{
	char			*name;
	int				(*com)(char **, char ***);
}					t_command;

int					exec_com(char *input, char ***env);
int					ft_echo(char **com, char ***env);
int					ft_cd(char **com, char ***env);
int					ft_setenv(char **com, char ***env);
int					ft_unsetenv(char **com, char ***env);
int					ft_env(char **com, char ***env);
char				**add_env(char ***env, char **add);

#endif
