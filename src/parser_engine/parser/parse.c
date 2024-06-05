/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:40:26 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/06/05 13:17:53 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../include/minishell.h"

static t_token	*search(t_token *from, int name, int direction)
{
	if (direction == FORWARDS)
	{
		while (from)
		{
			if (name == NOT_OP && from->type == COMMAND)
				return (from);
			else if (from->type == OPERATOR && from->name != name)
				return (NULL);
			else if (from->name == name && name != NOT_OP)
				return (from);
			from = from->next;
		}
	}
	else
	{
		while (from)
		{
			if (name == NOT_OP && from->type == COMMAND)
				return (from);
			else if (from->name == name && name != NOT_OP)
				return (from);
			from = from->prev;
		}
	}
	return (NULL);
}

static void	build(t_token *token, int *checksum)
{
	t_token	*search_token;

	token->subtree = malloc(sizeof(t_ast));
	token->subtree->left = malloc(sizeof(t_ast));
	token->subtree->token = token;
	token->subtree->left->token = search(token->prev, NOT_OP, BACKWARDS);
	search_token = search(token->next, PIPE, FORWARDS);
	if (search_token)
		token->subtree->right = search_token->subtree;
	else
	{
		token->subtree->right = malloc(sizeof(t_ast));
		token->subtree->right->token = token->next;
		*checksum += 1;
	}
	*checksum += 2;
}

int	build_pipelines(t_token *token)
{
	int		checksum;

	checksum = 0;
	while (token)
	{
		if (token->name == PIPE)
			build(token, &checksum);
		token = token->prev;
	}
	return (checksum);
}

int	connect_pipelines(t_token *token)
{
	t_ast	*left_connector_subtree;
	t_ast	*left_pipeline_subtree;
	t_token	*left_child;
	t_token	*search_token;
	int		checksum;

	left_connector_subtree = NULL;
	left_pipeline_subtree = NULL;
	left_child = NULL;
	checksum = 0;
	while (token)
	{
		if (token->type == COMMAND)
			left_child = token;
		if (token->name == PIPE && !left_pipeline_subtree)
			left_pipeline_subtree = token->subtree;
		if (token->name == AND || token->name == OR)
		{
			token->subtree = malloc(sizeof(t_ast));
			token->subtree->token = token;
			if (left_connector_subtree)
				token->subtree->left = left_connector_subtree;
			else if (left_pipeline_subtree)
				token->subtree->left = left_pipeline_subtree;
			else
			{
				token->subtree->left = malloc(sizeof(t_ast));
				token->subtree->left->token = left_child;
			}
			search_token = search(token->next, PIPE, FORWARDS);
			if (search_token)
				token->subtree->right = search_token->subtree;
			else
			{
				token->subtree->right = malloc(sizeof(t_ast));
				token->subtree->right->token = token->next;
			}
			left_connector_subtree = token->subtree;
			left_pipeline_subtree = NULL;
			checksum += 3;
		}
		token = token->next;
	}
	return (checksum);
}
