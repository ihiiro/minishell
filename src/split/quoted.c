/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoted.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:34:01 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/06/24 16:42:48 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	skip_quoted(char *str, int *i)
{
	if (str[*i] && str[*i] == '"')
	{
		*i += 1;
		while (str[*i] && str[*i] != '"')
			*i += 1;
	}
	else if (str[*i] && str[*i] == '\'')
	{
		*i += 1;
		while (str[*i] && str[*i] != '\'')
			*i += 1;
	}
}

void	count_quoted_len(char *str, int *len, char *charset)
{
	char	quote;

	quote = *str;
	*len += 1;
	while (str[*len] && str[*len] != quote)
		*len += 1;
	*len += 1;
	while (str[*len] && !in_charset(str[*len], charset))
		*len += 1;
}
