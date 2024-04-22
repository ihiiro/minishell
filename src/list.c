/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:54:39 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/04/22 18:22:04 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/minishell.h"

// NOTE: clearing function!!

void	append(t_token *node, t_token **list)
{
	t_token	*prev;

	if (!*list)
	{
		*list = node;
		(*list)->last = node;
		return ;
	}
	prev = (*list)->last;
	node->prev = prev;
	(*list)->last = node;
	prev->next = node;
}

t_token	*init_node(char *word)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	node->next = NULL;
	node->prev = NULL;
	node->type = -1;
	node->word = word;
	return (node);
}
