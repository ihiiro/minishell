/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:58:57 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/06/13 00:59:41 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_operator(char *word)
{
	if (word[0] == '&' && word[1] == '&')
		return (1);
	else if (word[0] == '|' && word[1] == '|')
		return (1);
	else if (word[0] == '|')
		return (1);
	else if (word[0] == '>' && word[1] == '>')
		return (1);
	else if (word[0] == '>')
		return (1);
	else if (word[0] == '<' && word[1] == '<')
		return (1);
	else if (word[0] == '<')
		return (1);
	return (0);
}
