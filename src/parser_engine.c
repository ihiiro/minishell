/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_engine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:56:13 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/04/23 12:22:04 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/minishell.h"

static int	operator(char *word)
{
	if ((word[0] == '&' && word[1] == '&')
		|| word[0] == '|'
		|| word[0] == '>'
		|| word[0] == '<')
		return (1);
	return (0);
}

static void	classify(t_token *token_list)
{
	int	prev_type;

	prev_type = -1;
	while (token_list)
	{
		if (prev_type == -1)
			token_list->type = COMMAND;
		else if (operator(token_list->word))
			token_list->type = OPERATOR;
		else if (prev_type == COMMAND)
			token_list->type = ARGUMENT;
		else if (prev_type == ARGUMENT)
			token_list->type = ARGUMENT;
		else if (prev_type == OPERATOR)
			token_list->type = COMMAND;
		prev_type = token_list->type;
		token_list = token_list->next;
	}
}

t_token	*tokenize(char **word_list)
{
	t_token	*token_list;
	t_token	*node;

	token_list = NULL;
	// while (*word_list)
	// {
		if (multi_token(*word_list))
			
		else
		{
			node = init_node(*word_list);
			append(node, &token_list);
		}
		word_list++;
	}
	classify(token_list);
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
