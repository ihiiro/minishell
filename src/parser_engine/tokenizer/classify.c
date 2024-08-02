/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 01:27:30 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/08/02 01:28:03 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	init_token_control_vars(t_token *token)
{
	token->subtree = NULL;
	token->subshell = 0;
	token->expansion_indices = gc_malloc(sizeof(size_t), COLLECT);
	token->expansion_indices[0] = 0;
	token->expand_wild = 0;
}

void	classify(t_token *token_list)
{
	int	prev_type;

	prev_type = NOTHING_TYPED;
	while (token_list)
	{
		init_token_control_vars(token_list);
		if (token_list->word[0] == '(')
			token_list->type = PARA_OPEN;
		else if (token_list->word[0] == ')')
			token_list->type = PARA_CLOSE;
		else if (is_operator(token_list->word))
			token_list->type = OPERATOR;
		else if (prev_type == NOTHING_TYPED)
			token_list->type = COMMAND;
		else if (prev_type == COMMAND)
			token_list->type = ARGUMENT;
		else if (prev_type == ARGUMENT)
			token_list->type = ARGUMENT;
		else if (prev_type == OPERATOR || prev_type == PARA_OPEN)
			token_list->type = COMMAND;
		prev_type = token_list->type;
		token_list = token_list->next;
	}
}
