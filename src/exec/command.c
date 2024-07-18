/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:22 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/18 11:52:22 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	command(t_ast *ast, t_shell *sh, int fd)
{
	char	**env;

	if (!ast || ast->token->type != COMMAND)
		return ;
	if (is_builtin(ast->token->word))
		builtins_exe(ast->token->word, ast, sh);
	else if (!ft_strncmp(ast->token->word, "./minishell", 12))
		shlvl_check(ast->token->word, &sh->env);
	else if (ast->token->type == COMMAND)
	{
		env = copy_env_to_arr(sh->env);
		sh->exit_status = execute_cmd(ast->token->args, env, sh);
		free_split(env);
	}
}
