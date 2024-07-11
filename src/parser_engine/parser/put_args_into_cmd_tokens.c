/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_args_into_cmd_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:06:58 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/11 18:45:46 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	count_args(t_token *cmd)
{
	int	arg_count;

	arg_count = 0;
	while (cmd && cmd->name != AND && cmd->name != OR
		&& cmd->name != PIPE)
	{
		if (cmd->type == ARGUMENT)
			arg_count++;
		cmd = cmd->next;
	}
	return (arg_count);
}

static void	fill(char **cmd_args_array, t_token *arg_list)
{
	int	i;

	i = 0;
	while (arg_list && arg_list->name != AND && arg_list->name != OR
		&& arg_list->name != PIPE)
	{
		if (arg_list->type == ARGUMENT)
		{
			cmd_args_array[i] = arg_list->word;
			i++;
		}
		arg_list = arg_list->next;
	}
	cmd_args_array[i] = NULL;
}

void	put_args_into_cmd_tokens(t_token *tokens)
{
	int	arg_count;

	while (tokens)
	{
		if (tokens->type == COMMAND)
		{
			arg_count = count_args(tokens);
			tokens->args = gc_malloc(sizeof(char *) * (arg_count + 1));
			fill(tokens->args, tokens);
		}
		tokens = tokens->next;
	}
}
