/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:40:26 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/06/04 15:06:58 by yel-yaqi         ###   ########.fr       */
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
