/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_engine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:56:13 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/04/22 16:59:28 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/minishell.h"

#include <stdio.h>
t_token	*tokenize(char **word_list)
{
	t_token	*token_list;
	t_token	*node;

	token_list = NULL;
	while (*word_list)
	{
		node = init_node(*word_list);
		append(node, token_list);
		word_list++;
	}
	return (token_list);
}

/*

()
&&
||
<
>
<<
>>
|

(a * b) + (c * d)
(echo hi && echo sup) || (echo bye && echo die)

a && b || c | d > e

a && ( b || c ) | d > e

a && ( b || c | ( f && g ) ) | d > e



*/

#include <stdio.h>
t_token	*prioritize(t_token *token_list)
{
	// t_token	*ptr;

	// ptr = token_list;
	// while (ptr)
	// {
	// 	printf("%s|%d\n", ptr->word, ptr->type);
	// 	ptr = ptr->next;
	// }
	return (token_list);
}
