/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_engine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:56:13 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/04/20 11:12:13 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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