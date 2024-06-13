/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:42:17 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/06/13 15:21:55 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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
	if (!root && start->type == PARA)
		root = start->subtree;
	if (!root && start->next->type == PARA)
		root = start->next->subtree;
	return (root);
}
