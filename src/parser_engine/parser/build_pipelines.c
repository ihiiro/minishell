/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pipelines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:39:21 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/06/10 10:59:55 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../include/minishell.h"

t_token	*search(t_token *from, int name, int direction)
{
	if (direction == FORWARDS)
	{
		while (from && from->type != PARA_CLOSE)
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
		while (from && from->type != PARA_OPEN)
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
	token->subtree->left->left = NULL;
	token->subtree->left->right = NULL;
	search_token = search(token->next, PIPE, FORWARDS);
	if (search_token)
		token->subtree->right = search_token->subtree;
	else
	{
		token->subtree->right = malloc(sizeof(t_ast));
		token->subtree->right->token = token->next;
		token->subtree->right->left = NULL;
		token->subtree->right->right = NULL;
		*checksum += 1;
	}
	*checksum += 2;
}

int	build_pipelines(t_token *token)
{
	int		checksum;

	checksum = 0;
	while (token && token->type != PARA_OPEN)
	{
		if (token->name == PIPE)
			build(token, &checksum);
		token = token->prev;
	}
	return (checksum);
}
