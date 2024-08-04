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
	ast->token->args = check_expand(ast->token->args, sh, ast->token);
	if (!ast->token->args
		|| !ast->token->args[0])
		return ;
	if (is_builtin(ast->token->word))
		builtins_exe(ast->token->word, ast, sh);
	else if (!ft_strncmp(ast->token->word, "./minishell", 12))
		shlvl_check(ast->token->word, &sh->env, sh);
	else if (ast->token->type == COMMAND)
	{
		env = copy_env_to_arr(sh->env);
		if (ft_strncmp(ast->token->args[0], "", 1))
			sh->exit_status = execute_cmd(ast->token->args, env, sh);
	}
}

void	child_proc(char *path, char **cmd, char *env[])
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	execve(path, cmd, env);
	print_error(cmd[0], MSG_NOPERM);
	gc_malloc(0, 0);
	exit(ERR_NOPERM);
}

int	exit_status_code(int exit_code)
{
	if (WIFSIGNALED(exit_code))
	{
		if (WTERMSIG(exit_code) == SIGINT)
			write (1, "\n", 1);
		else if (WTERMSIG(exit_code) == SIGQUIT)
			printf("Quit: 3\n");
		return (128 + WTERMSIG(exit_code));
	}
	return (WEXITSTATUS(exit_code));
}

int	execute_cmd(char **cmd, char *env[], t_shell *sh)
{
	char	*path;
	char	*path_env;
	int		pid;

	path_env = search_env(sh->env, "PATH");
	if (!path_env)
		return (print_error(cmd[0], MSG_NOFILE), ERR_NOFILE);
	path = find_path(cmd[0], path_env);
	if (!path)
		return (print_error(cmd[0], MSG_NOCMD), ERR_NOCMD);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (!pid)
		child_proc(path, cmd, env);
	else
		if (waitpid(pid, &sh->exit_status, 0) < 0)
			return (print_error("waitpid", NULL));
	return (exit_status_code(sh->exit_status));
}
