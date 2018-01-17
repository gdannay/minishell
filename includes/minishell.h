/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 13:46:50 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/17 13:45:29 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

int					exec_com(char **com, char ***env);
int					ft_echo(char **com, char ***env);
int					ft_cd(char **com, char ***env);
int					ft_setenv(char **com, char ***env);
int					ft_unsetenv(char **com, char ***env);
int					ft_env(char **com, char ***env);
char				**add_env(char ***env, char **add);
int					search_bina(char **com, char ***env);
void				free_env(char ***env);
char				*manage_path(char *str, char **rest);
int					echap(char **tmp, char **input, char *open);
int					error_mes(char *str);
int					error_alphanum(void);
int					error_many_arguments(char *str);
int					ft_cd_error(char **com);
char				*get_home(char *path, char ***env);
int					search_env(char ***env, char *var, size_t length);

#endif
