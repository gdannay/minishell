/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 10:03:52 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/08 16:36:16 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	error_mes(char *str)
{
	write(2, "minishell: command not found: ", 30);
	ft_printf("%s\n", str);
	return (0);
}

static int	exec(char **com, char **env, char **command)
{
	pid_t	father;
	int		status;

	if ((father = fork()) < 0)
		return (1);
	if (father > 0 && wait(&status) == -1)
		return (1);
	else if (father == 0)
		execve(*command, com, env);
	ft_strdel(command);
	return (0);
}

static int	parse_path(char **com, char **env, char *path)
{
	DIR				*rep;
	struct dirent	*fichier;
	char			*command;

	if ((rep = opendir(path)))
	{
//		dprintf(1, "TESt =%s %s\n", path, com[0]);
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

static char		**failcom(char **com, char *exec)
{
	char	**newcom;
	int		i;

	i = 0;
	while (com && com[i])
		i++;
	if ((newcom = (char **)malloc(sizeof(char *) * (i + 2))) == NULL)
		return (NULL);
	newcom[0] = ft_strdup(exec);
	i = 0;
	while (com && com[++i])
		newcom[i] = ft_strdup(com[i]);
	newcom[i] = 0;
	return (newcom);
}

static int	exec_file(char **com, char **env)
{
	char	*path;
	char	*exec;
	char	**newcom;

	path = NULL;
	if ((path = manage_path(com[0], &exec)) == NULL
			|| (newcom = failcom(com, exec)) == NULL)
		return (1);
	if (parse_path(newcom, env, path))
		error_mes(com[0]);
	ft_strdel(&path);
	ft_strdel(&exec);
	free_env(&newcom);
	return (0);
}

int			search_bina(char **com, char ***env)
{
	int		i;
	char	**path;

	i = 0;
	if (env && *env)
	{
		while ((*env)[i] && ft_strncmp((*env)[i], "PATH", 4))
			i++;
		if (!((*env)[i]))
			return (error_mes(com[0]));
		if ((path = ft_strsplit(((*env)[i] + 5), ':')) == NULL)
			return (1);
		i = 0;
		while (path[i] && parse_path(com, (*env), path[i]))
			i++;
		if (!(path[i]) && exec_file(com, *env))
			return (1);
		free_env(&path);
	}
	else if (exec_file(com, NULL))
		return (1);
	return (0);
}
