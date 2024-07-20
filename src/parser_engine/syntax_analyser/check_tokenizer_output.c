/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokenizer_output.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:25:55 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/20 16:34:28 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	syntax_error(t_token *tokens)
{
	if (!tokens)
		ft_printf(STDERR_FILENO,
			"msh: syntax error near unexpected token `newline'\n");
	else
		ft_printf(STDERR_FILENO,
			"msh: syntax error near unexpected token `%s'\n", tokens->word);
}

static int	check_operators(t_token *tokens)
{
	if (is_operator(tokens->word) && tokens->type != OPERATOR)
		return (syntax_error(tokens), 0);
	else if (tokens->prev && is_operator(tokens->prev->word)
		&& !is_redir_operator(tokens->prev)
		&& !is_heredoc_operator(tokens->prev) && is_operator(tokens->word)
		&& !is_redir_operator(tokens) && !is_heredoc_operator(tokens))
		return (syntax_error(tokens), 0);
	else if (tokens->prev && strequal("(", tokens->prev->word)
		&& is_operator(tokens->word)
		&& !is_redir_operator(tokens)
		&& !is_heredoc_operator(tokens))
		return (syntax_error(tokens), 0);
	else if (!tokens->prev && is_operator(tokens->word)
		&& !is_redir_operator(tokens)
		&& !is_heredoc_operator(tokens))
		return (syntax_error(tokens), 0);
	return (1);
}

int	check_tokenizer_output(t_token *tokens)
{
	while (tokens)
	{
		if (!check_operators(tokens))
			return (0);
		else if ((strequal("(", tokens->word) || strequal(")", tokens->word))
			&& tokens->type != PARA_OPEN && tokens->type != PARA_CLOSE)
			return (syntax_error(tokens), 0);
		else if (tokens->prev && strequal(")", tokens->prev->word)
			&& strequal("(", tokens->word))
			return (syntax_error(tokens), 0);
		else if (tokens->prev && is_operator(tokens->prev->word)
			&& strequal(")", tokens->word))
			return (syntax_error(tokens), 0);
		tokens = tokens->next;
	}
	return (1);
}
