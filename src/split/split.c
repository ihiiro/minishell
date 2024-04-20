/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:45:54 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/04/20 12:25:53 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../include/minishell.h"

static int	cnt_substrs(char const *s, char c)
{
	int	cnt;

	cnt = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			cnt++;
		while (*s && *s != c)
			s++;
	}
	return (cnt);
}

static char	**free_substrs(char **substrs)
{
	int	i;

	i = 0;
	while (substrs[i])
	{
		free(substrs[i]);
		i++;
	}
	free(substrs);
	return (NULL);
}

static void	helper(char const *s, int *len, char c)
{
	if (ft_strchr(s, c))
		*len = ft_strchr(s, c) - s;
	else
		*len = ft_strlen(s);
}

char	**ft_split(char const *s, char c)
{
	char	**substrs;
	int		i;
	int		len;

	if (!s)
		return (NULL);
	substrs = (char **)malloc((cnt_substrs(s, c) + 1) * sizeof(char *));
	if (!substrs)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			helper(s, &len, c);
			substrs[i] = ft_substr(s, 0, len);
			if (!substrs[i++])
				return (free_substrs(substrs));
			s += len;
		}
	}
	substrs[i] = NULL;
	return (substrs);
}
