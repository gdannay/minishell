/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 16:06:30 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/17 16:48:37 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**add_env(char ***env, char **add)
{
	int		i;
	char	**new;

	i = 0;
	while (env && (*env) && (*env)[i])
		i++;
	if ((new = (char **)malloc(sizeof(char *) * (i + 2))) == NULL)
		return (NULL);
	i = 0;
	while (env && (*env) && (*env)[i])
	{
		new[i] = ft_strdup((*env)[i]);
		ft_strdel(&(*env)[i]);
		i++;
	}
	if (*env)
		free(*env);
	new[i] = *add;
	new[i + 1] = 0;
	return (new);
}

int				ft_setenv(char **com, char ***ev)
{
	int		i;
	char	*new;

	i = 0;
	if (!(com[0]))
		return (ft_env(com, ev));
	while (com[0][i] && (ft_isdigit(com[0][i]) || ft_isalpha(com[0][i])))
		i++;
	if (com[0][i])
		return (error_alphanum());
	if (com[0] && com[1] && com[2] && com[3])
		return (error_many_arguments("setenv"));
	i = search_env(ev, com[0], ft_strlen(com[0]));
	if ((new = ft_joinwchar(com[0], com[1], '=')) == NULL)
		return (1);
	if (*ev && (*ev)[i] && com[0] && com[1] && com[2] && com[2][0] == '0')
		ft_strdel(&new);
	else if (ev && (*ev) && (*ev)[i])
	{
		ft_strdel(&(*ev)[i]);
		(*ev)[i] = new;
	}
	else if (ev && (*ev = add_env(ev, &new)) == NULL)
		return (1);
	return (0);
}

static char		**del_env(char ***env, int del)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	while ((*env)[i])
		i++;
	if ((new = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (NULL);
	i = -1;
	while ((*env)[++i])
	{
		if (i != del)
		{
			new[j] = ft_strdup((*env)[i]);
			j++;
		}
		ft_strdel(&(*env)[i]);
	}
	free(*env);
	new[j] = 0;
	return (new);
}

int				ft_unsetenv(char **com, char ***env)
{
	int		i;

	i = 0;
	if (!(com[0]))
		return (ft_env(com, env));
	while (env && (*env) && (*env)[i]
			&& ft_strncmp(com[0], (*env)[i], ft_strlen(com[0])))
		i++;
	if (env && (*env) && (*env)[i])
		(*env) = del_env(env, i);
	return (0);
}
