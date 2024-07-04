/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 11:10:21 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/04 12:22:13 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_ast	*get_right_redir_tree_root(t_token *tokens)
{
	t_token	*search_token;

	search_token = search(tokens, REDIR_IN, FORWARDS);
	if (!search_token)
		search_token = search(tokens, REDIR_OUT, FORWARDS);
	if (!search_token)
		search_token = search(tokens, REDIR_APP, FORWARDS);
	if (!search_token)
		search_token = search(tokens, HERE_DOC, FORWARDS);
	if (!search_token)
		return (NULL);
	else
		return (search_token->subtree);
}

void	connect_redirections(t_token *tokens)
{
	t_ast	*left_redir_tree_root;
	t_ast	*right_redir_tree_root;

	left_redir_tree_root = NULL;
	right_redir_tree_root = NULL;
	while (tokens)
	{
		if ((is_redir_operator(tokens) || is_heredoc_operator(tokens))
			&& !left_redir_tree_root)
			left_redir_tree_root = tokens->subtree;
		if (tokens->name == PIPE || tokens->name == AND || tokens->name == OR)
		{
			if (left_redir_tree_root && left_redir_tree_root != right_redir_tree_root)
				tokens->subtree->left = left_redir_tree_root;
			left_redir_tree_root = NULL;
			right_redir_tree_root = get_right_redir_tree_root(tokens);
			if (right_redir_tree_root)
				tokens->subtree->right = right_redir_tree_root;
		}
		tokens = tokens->next;
	}
}
