/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdannay <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:54:42 by gdannay           #+#    #+#             */
/*   Updated: 2018/01/11 19:08:15 by gdannay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_next(char **tmp, char **input, char open)
{
	char	*tmp2;

	tmp2 = *tmp;
	if (open != '\\')
	{
		if (!(*tmp = ft_strjoinwq(tmp2, "\n", -1)))
			return (1);
		ft_strdel(&tmp2);
	}
	tmp2 = *tmp;
	if (!(*tmp = ft_strjoinwq(tmp2, *input, -1)))
		return (1);
	ft_strdel(&tmp2);
	return (0);
}

static int	open_end(char **tmp, char **input, char open)
{
	char	*tmp2;

	tmp2 = *tmp;
	if (open != -'\\')
	{
		tmp2 = *tmp;
		if (!(*tmp = ft_strjoinwq(tmp2, "\n", -1)))
			return (1);
		ft_strdel(&tmp2);
		if (!(tmp2 = ft_strdupwq(*input, -open)))
			return (1);
		ft_strdel(input);
		*input = tmp2;
		tmp2 = *tmp;
	}
	if (!(*tmp = ft_strjoinwq(tmp2, *input, -1)))
		return (1);
	ft_strdel(&tmp2);
	return (0);
}

static char	check_echap(char **input, char open)
{
	int		i;

	i = -1;
	while ((*input)[++i])
	{
		if (open <= 0 && ((*input)[i] == '\''
				|| (*input)[i] == '\"' || ((*input)[i] == '\\'
				&& !(*input)[i + 1]
				&& (i == 0 || (*input)[i - 1] != '\\'))))
			open = (*input)[i];
		else if (open == (*input)[i])
			open = -(*input)[i];
	}
	return (open);
}

static int	print_echap(char *open)
{
	if (*open == '\\')
	{
		ft_printf("> ");
		*open = -'\\';
	}
	if (*open == '\'')
		ft_printf("quote> ");
	else if (*open == '\"')
		ft_printf("dquote> ");
	return (-1);
}

int			echap(char **tmp, char **input, char *open)
{
	int ret;

	ret = 0;
	*open = check_echap(input, *open);
	if (*tmp && *open > 0)
		ret = open_next(tmp, input, *open);
	else if (*tmp && *open <= 0)
		ret = open_end(tmp, input, *open);
	else if (*open <= 0 || !(*tmp))
	{
		if (*open == '\\' &&
		!(*tmp = ft_strndupwq(*input, ft_strlen(*tmp) + ft_strlen(*input) - 1)))
			return (1);
		else if (*open != '\\' && !(*tmp = ft_strdupwq(*input, -(*open))))
			return (1);
	}
	else if (!(*tmp = ft_strdup(*input)))
		return (1);
	if (ret)
		return (1);
	ft_strdel(input);
	if (*open > 0)
		return (print_echap(open));
	return (0);
}
