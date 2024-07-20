/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:18:10 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/20 13:28:25 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"


static int	check_tokenizer_output(t_token *tokens)
{
	while (tokens)
	{
		if (is_operator(tokens->word) && tokens->type != OPERATOR)
			return (ft_printf(STDOUT_FILENO, "msh: syntax error near unexpected token `%s'\n", tokens->word), 0);
		else if ((strequal("(", tokens->word) || strequal(")", tokens->word))
			&& tokens->type != PARA_OPEN && tokens->type != PARA_CLOSE)
			return (ft_printf(STDOUT_FILENO, "msh: syntax error near unexpected token `%s'\n", tokens->word), 0);
		else if (tokens->prev && is_operator(tokens->prev->word)
			&& !is_redir_operator(tokens->prev)
			&& !is_heredoc_operator(tokens->prev) && is_operator(tokens->word)
			&& !is_redir_operator(tokens) && !is_heredoc_operator(tokens))
			return (ft_printf(STDOUT_FILENO, "msh: syntax error near unexpected token `%s'\n", tokens->word), 0);
		else if (tokens->prev && strequal("(", tokens->prev->word) && is_operator(tokens->word)
			&& !is_redir_operator(tokens)
			&& !is_heredoc_operator(tokens))
			return (ft_printf(STDOUT_FILENO, "msh: syntax error near unexpected token `%s'\n", tokens->word), 0);
		else if (!tokens->prev && is_operator(tokens->word)
			&& !is_redir_operator(tokens)
			&& !is_heredoc_operator(tokens))
			return (ft_printf(STDOUT_FILENO, "msh: syntax error near unexpected token `%s'\n", tokens->word), 0);
		else if (tokens->prev && strequal(")", tokens->prev->word) && strequal("(", tokens->word))
			return (ft_printf(STDOUT_FILENO, "msh: syntax error near unexpected token `%s'\n", tokens->word), 0);
		tokens = tokens->next;
	}
	return (1);
}

static int	check_para_balance(t_token *tokens)
{
	int	balance;

	balance = 0;
	while (tokens)
	{
		if (strequal("(", tokens->word))
			balance++;
		else if (strequal(")", tokens->word))
			balance--;
		tokens = tokens->next;
	}
	if (balance > 0)
		return (2);
	else if (balance < 0)
		return (ft_printf(STDOUT_FILENO, "msh: syntax error near unexpected token `)'\n"), 0);
	return (1);
}

static int	para_empty(t_token *tokens)
{
	int	empty;

	empty = 0;
	while (tokens)
	{
		if (strequal("(", tokens->word))
			empty = 1;
		else if (strequal(")", tokens->word) && empty)
			return (ft_printf(STDOUT_FILENO, "msh: syntax error near unexpected token `)'\n"), 1);
		else
			empty = 0;
		tokens = tokens->next;
	}
	return (0);
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
	else if (para_empty(tokens))
		return (0);
	return (check_para_balance(tokens));
}
