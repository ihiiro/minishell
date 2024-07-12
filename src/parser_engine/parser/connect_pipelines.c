/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_pipelines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:40:26 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/12 12:23:45 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../include/minishell.h"

static void	connect_left(t_token *token, t_token *left_child,
	t_ast *left_pipeline_subtree, t_ast *left_connector_subtree)
{
	token->subtree = gc_malloc(sizeof(t_ast), COLLECT);
	token->subtree->token = token;
	if (left_connector_subtree)
		token->subtree->left = left_connector_subtree;
	else if (left_pipeline_subtree)
		token->subtree->left = left_pipeline_subtree;
	else
	{
		token->subtree->left = gc_malloc(sizeof(t_ast), COLLECT);
		token->subtree->left->token = left_child;
		token->subtree->left->left = NULL;
		token->subtree->left->right = NULL;
	}
}

static void	connect_right(t_token *token)
{
	t_token	*search_token;

	search_token = search(token->next, PIPE, FORWARDS);
	if (search_token)
		token->subtree->right = search_token->subtree;
	else
	{
		token->subtree->right = gc_malloc(sizeof(t_ast), COLLECT);
		token->subtree->right->token = token->next;
		token->subtree->right->right = NULL;
		token->subtree->right->left = NULL;
	}
}

void	connect_pipelines(t_token *token)
{
	t_ast	*left_connector_subtree;
	t_ast	*left_pipeline_subtree;
	t_token	*left_child;

	left_connector_subtree = NULL;
	left_pipeline_subtree = NULL;
	left_child = NULL;
	while (token && token->type != PARA_CLOSE)
	{
		if (token->type == COMMAND || token->type == PARA)
			left_child = token;
		if (token->name == PIPE && !left_pipeline_subtree)
			left_pipeline_subtree = token->subtree;
		if (token->name == AND || token->name == OR)
		{
			connect_left(token, left_child, left_pipeline_subtree,
				left_connector_subtree);
			connect_right(token);
			left_connector_subtree = token->subtree;
			left_pipeline_subtree = NULL;
		}
		token = token->next;
	}
}
