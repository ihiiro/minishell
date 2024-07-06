/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_args_into_cmd_tokens.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:06:58 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/06 16:42:52 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	count_args(t_token *arg_list)
{
	int	arg_count;

	arg_count = 0;
	while (arg_list && arg_list->type == ARGUMENT)
	{
		arg_count++;
		arg_list = arg_list->next;
	}
	return (arg_count);
}

static void	fill(char **cmd_args, t_token *arg_list)
{
	int i;

	i = 0;
	while (arg_list && arg_list->type == ARGUMENT)
	{
		cmd_args[i] = arg_list->word;
		i++;
		arg_list = arg_list->next;
	}
	cmd_args[i] = NULL;
}

static void	put_into_cmd(t_token *cmd)
{
	int	arg_count;

	arg_count = count_args(cmd->next);
	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	fill(cmd->args, cmd->next);
}

void	put_args_into_cmd_tokens(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == COMMAND)
			put_into_cmd(tokens);
		tokens = tokens->next;
	}
}
