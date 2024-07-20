/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:18:10 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/20 10:44:11 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static bool	strequal(char *str0, char *str1)
{
	int	rslt = ft_strcmp(str0, str1);
	if (rslt)
		return (false);
	else
		return (true);
}


static int	check_tokenizer_output(t_token *tokens)
{
	while (tokens)
	{
		if (is_operator(tokens->word) && tokens->type != OPERATOR)
			return (0);
		else if ((strequal("(", tokens->word) || strequal(")", tokens->word))
			&& tokens->type != PARA_OPEN && tokens->type != PARA_CLOSE)
			return (0);
		else if (tokens->prev && is_operator(tokens->prev->word)
			&& !is_redir_operator(tokens->prev)
			&& !is_heredoc_operator(tokens->prev) && is_operator(tokens->word)
			&& !is_redir_operator(tokens)
			&& !is_heredoc_operator(tokens))
			return (0);
		else if (tokens->prev && strequal("(", tokens->prev->word) && is_operator(tokens->word)
			&& !is_redir_operator(tokens)
			&& !is_heredoc_operator(tokens))
			return (0);
		else if (!tokens->prev && is_operator(tokens->word)
			&& !is_redir_operator(tokens)
			&& !is_heredoc_operator(tokens))
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

int	check_tokens(char *line)
{
	char	**word_list;
	t_token	*tokens;

	word_list = ft_split(line, " \t");
	tokens = NULL;
	tokenize(word_list, &tokens);
	name_operators(tokens);
	type_files_and_limiters(tokens);
	make_irregular_arguments(tokens);
	if (!check_tokenizer_output(tokens))
		return (0);
	return (1);
}
