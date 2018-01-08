/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:03:52 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/08 11:36:12 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_mes(char *str)
{
	write(2, "minishell: command not found: ", 30);
	ft_printf("%s\n", str);
	return (0);
}

static int	exec(char **com, char ***env, char **command)
{
	pid_t	father;
	int		status;

	if ((father = fork()) < 0)
		return (1);
	if (father > 0 && wait(&status) == -1)
		return (1);
	else if (father == 0)
		execve(*command, com, (*env));
	ft_strdel(command);
	return (0);
}

static int	parse_path(char **com, char ***env, char *path)
{
	DIR				*rep;
	struct dirent	*fichier;
	char			*command;

	if ((rep = opendir(path)))
	{
		fichier = readdir(rep);
		while (fichier && ft_strcmp(fichier->d_name, com[0]))
			fichier = readdir(rep);
		if (closedir(rep) == -1)
			return (1);
		if (fichier && fichier->d_type != DT_DIR)
		{
			if ((command = ft_joinpath(path, com[0])) == NULL
				|| exec(com, env, &command))
				return (1);
			else
				return (0);
		}
	}
	return (1);
}

int			search_bina(char **com, char ***env)
{
	int				i;
	char			**path;

	i = 0;
	while ((*env)[i] && ft_strncmp((*env)[i], "PATH", 4))
		i++;
	if (!((*env)[i]))
		return (error_mes(com[0]));
	if ((path = ft_strsplit(((*env)[i] + 5), ':')) == NULL)
		return (1);
	i = 0;
	while (path[i] && parse_path(com, env, path[i]))
		i++;
	if (!(path[i]))
		error_mes(com[0]);
	i = -1;
	while (path[++i])
		ft_strdel(&(path[i]));
	free(path);
	return (0);
}
