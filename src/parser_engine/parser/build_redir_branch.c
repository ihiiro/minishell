/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redir_branch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 18:19:27 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/12 12:23:38 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_ast	*get_redir_tree_tail(t_token *tokens)
{
	while (tokens)
	{
		if (is_redir_operator(tokens) || is_heredoc_operator(tokens))
			return (tokens->subtree);
		else if (tokens->name == AND || tokens->name == OR
			|| tokens->name == PIPE)
			break ;
		tokens = tokens->next;
	}
	return (NULL);
}

void	build_compound(t_token *token, int marker)
{
	token->subtree = gc_malloc(sizeof(t_ast), COLLECT);
	token->subtree->token = token;
	if (marker)
	{
		token->subtree->left = gc_malloc(sizeof(t_ast), COLLECT);
		if (token->next && token->next->next
			&& token->next->next->type == COMMAND)
		{
			token->subtree->left->token = token->next->next;
			token->subtree->left->left = NULL;
			token->subtree->left->right = NULL;
		}
		else
			token->subtree->left = NULL;
	}
	else
		token->subtree->left = get_redir_tree_tail(token->next);
	token->subtree->right = gc_malloc(sizeof(t_ast), COLLECT);
	token->subtree->right->token = token->next;
	token->subtree->right->left = NULL;
	token->subtree->right->right = NULL;
}

void	build_simple(t_token *token, t_token *cmd)
{
	token->subtree = gc_malloc(sizeof(t_ast), COLLECT);
	token->subtree->token = token;
	if (cmd->type == PARA)
		token->subtree->left = cmd->subtree;
	else
	{
		token->subtree->left = gc_malloc(sizeof(t_ast), COLLECT);
		token->subtree->left->token = cmd;
		token->subtree->left->left = NULL;
		token->subtree->left->right = NULL;
	}
	token->subtree->right = gc_malloc(sizeof(t_ast), COLLECT);
	token->subtree->right->token = token->next;
	token->subtree->right->left = NULL;
	token->subtree->right->right = NULL;
}
