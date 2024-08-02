/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:56:13 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/08/02 16:11:03 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../include/minishell.h"

int	isspace_(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

static char	*strdup_quoted(char *str, size_t *i)
{
	size_t		quoted_len;
	size_t		size;
	char		*quoted;

	quoted_len = 0;
	while (str[quoted_len])
	{
		if (!is_quoted(str[quoted_len])
			&& (isspace_(str[quoted_len]) || is_operator(&str[quoted_len])
				|| str[quoted_len] == '(' || str[quoted_len] == ')'))
			break ;
		quoted_len++;
	}
	size = sizeof(char) * (quoted_len + 1);
	quoted = gc_malloc(size, COLLECT);
	ft_strlcpy(quoted, str, size);
	*i = quoted_len;
	return (quoted);
}

static void	append_multi(char *word, t_token **token_list)
{
	size_t		i;
	t_token		*node;

	i = 0;
	if (ft_strchr(word, '\'') || ft_strchr(word, '"'))
	{
		node = init_node(strdup_quoted(word, &i));
		append(node, token_list);
	}
	multi(&word[i], token_list);
}

void	tokenize(char **word_list, t_token **token_list)
{
	if (!*word_list)
	{
		classify(*token_list);
		return ;
	}
	append_multi(*word_list, token_list);
	tokenize(word_list + 1, token_list);
}
