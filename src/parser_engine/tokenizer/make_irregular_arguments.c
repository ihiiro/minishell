/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_irregular_arguments.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:26:01 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/07 11:37:47 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	make_irregular_arguments(t_token *tokens)
{
	t_token	*current_cmd;

	current_cmd = NULL;
	while (tokens)
	{
		if (tokens->type == COMMAND && !current_cmd)
			current_cmd = tokens;
		else if (tokens->type == COMMAND && current_cmd)
			tokens->type = ARGUMENT;
		else if (tokens->name == AND || tokens->name == OR
			|| tokens->name == PIPE)
			current_cmd = NULL;
		tokens = tokens->next;
	}
}
