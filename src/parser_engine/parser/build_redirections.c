/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:56:54 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/04 18:21:57 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_token	*get_cmd(t_token *token)
{
	while (token)
	{
		if (token->type == COMMAND || token->type == PARA)
			return (token);
		else if (token->name == AND || token->name == OR || token->name == PIPE)
			break ;
		token = token->prev;
	}
	return (NULL);
}

static void	build(t_token *token, int marker)
{
	t_token	*cmd;

	cmd = NULL;
	if (!token->next->next || (!is_redir_operator(token->next->next)
			&& !is_heredoc_operator(token->next->next) && marker))
		cmd = get_cmd(token);
	if (cmd)
		build_simple(token, cmd);
	else
		build_compound(token, marker);
}

void	build_redirections(t_token *tokens)
{
	int	marker;

	marker = 1;
	while (tokens && tokens->type != PARA_OPEN)
	{
		if (is_redir_operator(tokens) || is_heredoc_operator(tokens))
		{
			build(tokens, marker);
			marker = 0;
		}
		if (tokens->name == AND || tokens->name == OR || tokens->name == PIPE)
			marker = 1;
		tokens = tokens->prev;
	}
}
