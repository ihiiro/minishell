/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_irregular_arguments.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 11:26:01 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/08/07 14:00:40 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	lone_input(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->name == AND || tokens->name == OR
			|| tokens->name == PIPE)
			break ;
		if (tokens->name == REDIR_IN || tokens->type == ARGUMENT
			|| tokens->type == COMMAND)
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

void	make_irregular_arguments(t_token *tokens)
{
	t_token	*current_cmd;
	int		left_pipe;

	current_cmd = NULL;
	left_pipe = 0;
	while (tokens)
	{
		if (tokens->name == PIPE)
			left_pipe = 1;
		if (tokens->name == AND || tokens->name == OR)
			left_pipe = 0;
		if (tokens->type == COMMAND && !current_cmd)
			current_cmd = tokens;
		else if (tokens->type == COMMAND && current_cmd)
			tokens->type = ARGUMENT;
		else if (tokens->type == FILE && left_pipe
			&& tokens->prev->name == REDIR_IN
			&& lone_input(tokens))
			tokens->type = ARGUMENT;
		else if (tokens->name == AND || tokens->name == OR
			|| tokens->name == PIPE)
			current_cmd = NULL;
		tokens = tokens->next;
	}
}
