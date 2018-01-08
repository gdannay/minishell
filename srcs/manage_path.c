/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 15:18:48 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/08 16:16:04 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	last_slash(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str && str[i])
	{
		if (str[i] == '/')
			j = i;
		i++;
	}
	return (j);
}

char		*manage_path(char *str, char **rest)
{
	int		j;
	char	*path;

	j = last_slash(str);
	if (str == NULL || rest == NULL)
		return (NULL);
	if (str[j] == '/')
	{
		if ((path = ft_strndup(str, j)) == NULL)
			return (NULL);
		j++;
		if ((*rest = ft_strsub(str, j, ft_strlen(str) - (size_t)j)) == NULL)
			return (NULL);
		return (path);
	}
	if ((*rest = ft_strdup(str)) == NULL)
		return (NULL);
	return (ft_strdup("."));
}