/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:56:54 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/03 18:41:08 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_token	*get_cmd(t_token *token)
{
	while (token)
	{
		if (token->type == COMMAND)
			return (token);
		else if (token->name == AND || token->name == OR || token->name == PIPE)
			break ;
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

static void	build_compound(t_token *token, int marker)
{
	token->subtree = malloc(sizeof(t_ast));
	token->subtree->token = token;
	if (marker)
	{
		token->subtree->left = malloc(sizeof(t_ast));
		token->subtree->left->token = token->next->next;
		token->subtree->left->left = NULL;
		token->subtree->left->right = NULL;
	}
	else
		token->subtree->left = get_redir_tree_tail(token->next);
	token->subtree->right = malloc(sizeof(t_ast));
	token->subtree->right->token = token->next;
	token->subtree->right->left = NULL;
	token->subtree->right->right = NULL;
}

static void	build(t_token *token, int marker)
{
	t_token	*cmd;

	cmd = NULL;
	if (!token->next->next || (!is_redir_operator(token->next->next)
			&& !is_heredoc_operator(token->next->next) && marker))
		cmd = get_cmd(token);
	if (cmd)
	{
		token->subtree = malloc(sizeof(t_ast));
		token->subtree->token = token;
		token->subtree->left = malloc(sizeof(t_ast));
		token->subtree->right = malloc(sizeof(t_ast));
		token->subtree->left->token = cmd;
		token->subtree->left->left = NULL;
		token->subtree->left->right = NULL;
		token->subtree->right->token = token->next;
		token->subtree->right->left = NULL;
		token->subtree->right->right = NULL;
	}
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
		tokens = tokens->prev;
	}
}
