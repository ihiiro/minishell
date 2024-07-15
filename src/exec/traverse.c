/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:51:22 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/12 09:51:23 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	command(t_ast *ast, t_shell *sh)
{
	char	**env;

	if (is_builtin(ast->token->word))
		builtins_exe(ast->token->word, ast, sh);
	else if (!ft_strncmp(ast->token->word, "./minishell", 12))
		shlvl_check(ast->token->word, &sh->env);
	else if (ast->token->type == COMMAND)
	{
		env = copy_env_to_arr(sh->env);
		sh->exit_status = execute_cmd(ast->token->args, env, sh);
		free_split(env);
		return ;
	}
}

void	and_or_operators(t_ast *ast, t_shell *sh)
{
	if (ast->token->name == AND)
	{
		traverse_tree(ast->left, sh);
		if (!sh->exit_status)
			traverse_tree(ast->right, sh);
		else
			return ;
	}
	if (ast->token->name == OR)
	{
		traverse_tree(ast->left, sh);
		if (sh->exit_status != 0)
			traverse_tree(ast->right, sh);
		else
			return ;
	}
}

void	traverse_tree(t_ast *ast, t_shell *sh)
{
	if (!ast)
		return ;
	and_or_operators(ast, sh);
	command(ast, sh);
	return ;
}
