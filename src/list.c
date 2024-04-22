/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 16:54:39 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/04/22 17:07:24 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/minishell.h"

void	append(t_token *node, t_token *list)
{
	t_token	*prev;

	prev = list->last;
	if (prev)
		prev->next = node;
	node->prev = prev;
}

t_token	*init_node(char *word)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	node->next = NULL;
	node->prev = NULL;
	node->type = classify(word);
	node->word = word;
	return (node);
}
