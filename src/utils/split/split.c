/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 19:45:54 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/12 12:24:27 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../include/minishell.h"

int	in_charset(char c, char *charset)
{
	int	i;

	i = -1;
	while (charset[++i])
	{
		if (c == charset[i])
			return (1);
	}
	return (0);
}

int	count_substrs(char *str, char *charset)
{
	int	count;
	int	new_string;
	int	i;

	count = 0;
	i = -1;
	new_string = 1;
	while (str[++i])
	{
		if (!in_charset(str[i], charset) && new_string)
		{
			count++;
			new_string = 0;
		}
		else if (in_charset(str[i], charset) && !new_string)
			new_string = 1;
		skip_quoted(str, &i);
	}
	return (count);
}

static char	*split_strdup(char *str, char *charset)
{
	char	*cpy;
	int		len;
	int		i;
	char	*ptr;

	len = 0;
	i = 0;
	ptr = str;
	if (*str == '"' || *str == '\'')
		count_quoted_len(str, &len, charset);
	else
	{
		while (str[len] && !in_charset(str[len], charset))
			len++;
	}
	cpy = gc_malloc(len + 1, COLLECT);
	while (i < len)
	{
		cpy[i] = *ptr;
		ptr++;
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**ft_split(char *str, char *charset)
{
	char	**substrs;
	int		index;
	int		new_string;
	int		i;

	new_string = 1;
	index = 0;
	i = -1;
	substrs = gc_malloc(sizeof(char *)
			* count_substrs(str, charset) + sizeof(char *), COLLECT);
	while (str[++i])
	{
		if (!in_charset(str[i], charset) && new_string)
		{
			substrs[index] = split_strdup(&str[i], charset);
			index++;
			new_string = 0;
		}
		else if (in_charset(str[i], charset) && !new_string)
			new_string = 1;
		skip_quoted(str, &i);
	}
	substrs[index] = 0;
	return (substrs);
}
