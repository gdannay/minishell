/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 11:59:17 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/07 14:49:41 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_dstrdup(char **str)
{
	int		i;
	char	**cpy;

	i = 0;
	cpy = NULL;
	while (str && str[i])
		i++;
	if ((cpy = (char **)malloc(sizeof(char *) * (i + 1))) == NULL)
		return (NULL);
	cpy[i] = 0;
	i = -1;
	while (str && str[++i])
		cpy[i] = ft_strdup(str[i]);
	return (cpy);
}
