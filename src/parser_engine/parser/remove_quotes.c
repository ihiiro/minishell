/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 10:49:22 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/21 12:39:57 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static size_t	get_quoteless_len(char *word)
{
	size_t	len;
	size_t	i;
	int		opening_quote;
	int		is_quoted_rslt;

	len = 0;
	i = 0;
	opening_quote = 1;
	while (word[i])
	{
		is_quoted_rslt = is_quoted(word[i]);
		if (is_quoted_rslt && opening_quote)
			opening_quote = 0;
		else if (is_quoted_rslt && !opening_quote)
			len++;
		else if (word[i] != '\'' && word[i] != '"')
			len++;
		else if (!is_quoted_rslt)
			opening_quote = 1;
		i++;
	}
	return (len);
}

static void	copy_new_word_to_token(t_token *token, char *old_word)
{
	size_t	i;
	size_t	j;
	int		is_quoted_rslt;
	int		opening_quote;

	i = 0;
	j = 0;
	opening_quote = 1;
	while (old_word[i])
	{
		is_quoted_rslt = is_quoted(old_word[i]);
		if (is_quoted_rslt && opening_quote)
			opening_quote = 0;
		else if ((is_quoted_rslt && !opening_quote)
			|| (old_word[i] != '\'' && old_word[i] != '"'))
		{
			token->word[j] = old_word[i];
			j++;
		}
		else if (!is_quoted_rslt)
			opening_quote = 1;
		i++;
	}
	token->word[j] = '\0';
}

static void	unquote(t_token *token)
{
	size_t	quoteless_len;
	char	*old_word;

	old_word = token->word;
	quoteless_len = get_quoteless_len(old_word);
	token->word = gc_malloc(sizeof(char) * (quoteless_len + 1), COLLECT);
	copy_new_word_to_token(token, old_word);
}

void	remove_quotes(t_token *tokens)
{
	while (tokens)
	{
		unquote(tokens);
		tokens = tokens->next;
	}
}
