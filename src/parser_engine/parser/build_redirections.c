/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:56:54 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/03 17:41:31 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_token	*get_cmd(t_token *token)
{
	while (token)
	{
		if (token->type == COMMAND)
			return (token);
		token = token->prev;
	}
	return (NULL);
}

static t_ast	*get_redir_tree_tail(t_token *tokens)
{
	while (tokens)
	{
		if (is_redir_operator(tokens) || is_heredoc_operator(tokens))
			return (tokens->subtree);
		tokens = tokens->next;
	}
	return (NULL);
}

static void	build(t_token *token)
{
	t_token	*cmd;

	cmd = NULL;
	if (!token->next->next || (!is_redir_operator(token->next->next)
			&& !is_heredoc_operator(token->next->next)))
		cmd = get_cmd(token);
	if (cmd)
	{
		token->subtree = malloc(sizeof(t_ast));
		token->subtree->token = token;
		token->subtree->left = malloc(sizeof(t_ast));
		token->subtree->right = malloc(sizeof(t_ast));
		token->subtree->left->token = cmd;
		token->subtree->right->token = token->next;
	}
	else
	{
		token->subtree = malloc(sizeof(t_ast));
		token->subtree->token = token;
		token->subtree->left = get_redir_tree_tail(token->next);
		token->subtree->right = malloc(sizeof(t_ast));
		token->subtree->right->token = token->next;
	}
}

void	build_redirections(t_token *tokens)
{
	while (tokens && tokens->type != PARA_OPEN)
	{
		if (is_redir_operator(tokens) || is_heredoc_operator(tokens))
			build(tokens);
		tokens = tokens->prev;
	}
}
