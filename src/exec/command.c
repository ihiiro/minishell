/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:22 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/29 22:37:09 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	command(t_ast *ast, t_shell *sh)
{
	char	**env;

	if (!ast || ast->token->type != COMMAND)
		return ;
	ast->token->args = check_expand(ast->token->args, sh, ast->token->expansion_indices);
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

int	execute_cmd(char **cmd, char *env[], t_shell *sh)
{
	char	*path;
	char	*path_env;
	int		pid;

	path_env = search_env(sh->env, "PATH");
	if (!path_env)
		return (print_error(cmd[0], MSG_NOFILE), ERR_NOFILE);
	path = find_path(cmd[0], env, sh, path_env);
	if (!path)
		return (free(path), print_error(cmd[0], MSG_NOCMD), ERR_NOCMD);
	if (access(path, X_OK) != 0)
		return (free(path), print_error(cmd[0], MSG_NOPERM), ERR_NOPERM);
	pid = fork();
	if (!pid)
	{
		execve(path, cmd, env);
		free(path);
		exit(print_error(cmd[0], "execve"));
	}
	else
		if (waitpid(pid, &sh->exit_status, 0) < 0)
			return (free(path), print_error("waitpid", NULL));
	return (free(path), WEXITSTATUS(sh->exit_status));
}
