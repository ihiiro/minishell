/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:22 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/08 20:13:19 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	command(t_ast *ast, t_shell *sh)
{
	char	**env;

	if (!ast || ast->token->type != COMMAND
		|| sh->fork_err)
		return ;
	ast->token->args = check_expand(ast->token->args, sh, ast->token);
	if (!ast->token->args)
		return ;
	if (is_builtin(ast->token->args[0]))
		builtins_exe(ast->token->args[0], ast, sh);
	else if (!ft_strncmp(ast->token->word, "./minishell", 12))
		shlvl_check(ast->token->word, &sh->env, sh);
	else if (ast->token->type == COMMAND)
	{
		env = copy_env_to_arr(sh->env);
		if (!ast->token->args[0])
			sh->exit_status = exit_status_code(0);
		else
			sh->exit_status = execute_cmd(ast->token->args, env, sh, ast);
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

void	executes(char *path, char **cmd, char *env[])
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	execve(path, cmd, env);
	print_error(cmd[0], MSG_NOPERM);
	gc_malloc(0, 0);
}

int	execute_cmd(char **cmd, char *env[], t_shell *sh, t_ast *ast)
{
	char	*path;
	char	*path_env;
	int		pid;

	path_env = search_env(sh->env, "PATH");
	path = find_path(cmd[0], path_env);
	if (!path)
		return (ERR_NOCMD);
	ignore_sigs();
	if (ast->token->left_pipe == 1 || ast->token->right_pipe == 1)
		executes(path, cmd, env);
	else
	{
		pid = fork();
		if (pid < 0)
			return (fork_failed(sh->fork_err), 1);
		if (!pid)
			child_proc(path, cmd, env);
		else
			if (waitpid(pid, &sh->exit_status, 0) < 0)
				return (perror("waitpid"), 1);
		return (exit_status_code(sh->exit_status));
	}
	return (sh->exit_status);
}
