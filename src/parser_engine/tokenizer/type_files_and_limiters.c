/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_files_and_limiters.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:57:08 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/20 10:27:17 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft/libft.h"
#include "../../../include/minishell.h"

int	is_redir_operator(t_token *token)
{
	return (token->word && (!ft_strcmp("<", token->word)
			|| !ft_strcmp(">", token->word)
			|| !ft_strcmp(">>", token->word)));
}

int	is_heredoc_operator(t_token *token)
{
	return (token->word && !ft_strcmp("<<", token->word));
}

void	type_files_and_limiters(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->prev && is_redir_operator(tokens->prev))
			tokens->type = FILE;
		else if (tokens->prev && is_heredoc_operator(tokens->prev))
			tokens->type = LIMITER;
		else if (tokens->prev && tokens->prev->type == FILE
			&& !is_redir_operator(tokens) && !is_heredoc_operator(tokens)
			&& tokens->type != PARA_CLOSE
			&& tokens->type != OPERATOR)
			tokens->type = COMMAND;
		tokens = tokens->next;
	}
}
