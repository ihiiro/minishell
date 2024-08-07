/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:42:17 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/12 12:23:53 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../include/minishell.h"

static t_ast	*make_root_from_token(t_token *token)
{
	t_ast	*root;

	root = NULL;
	if (token)
	{
		root = gc_malloc(sizeof(t_ast), COLLECT);
		root->token = token;
		root->right = NULL;
		root->left = NULL;
	}
	return (root);
}

static t_ast	*get_redir_subtree(t_token *start)
{
	while (start)
	{
		if (is_redir_operator(start) || is_heredoc_operator(start))
			return (start->subtree);
		start = start->next;
	}
	return (NULL);
}

t_ast	*fetch_ast(t_token *tokens)
{
	t_ast	*root;
	t_token	*start;

	root = NULL;
	start = tokens;
	while (tokens && tokens->type != PARA_CLOSE)
	{
		if (tokens->name == PIPE && !root)
			root = tokens->subtree;
		if (tokens->name == AND || tokens->name == OR)
			root = tokens->subtree;
		tokens = tokens->next;
	}
	if (!root)
		root = get_redir_subtree(start);
	if (!root && start->type == PARA)
		root = start->subtree;
	if (!root && start->next && start->next->type == PARA)
		root = start->next->subtree;
	if (!root && start && start->type == PARA_OPEN)
		root = make_root_from_token(start->next);
	if (!root)
		root = make_root_from_token(start);
	return (root);
}
