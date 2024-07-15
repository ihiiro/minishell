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

void	second_child(t_ast *ast, t_shell *sh, int *fd, int *status)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		traverse_tree(ast->right, sh);
		exit(sh->exit_status);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, status, 0);
}

void	pipe_operator(t_ast *ast, t_shell *sh)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (!ast || ast->token->name != PIPE)
		return ;
	if (pipe(fd) < 0)
		return (perror("pipe"));
	pid = fork();
	if (pid < 0)
		return (perror("fork"));
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		traverse_tree(ast->left, sh);
		exit(sh->exit_status);
	}
	second_child(ast, sh, fd, &status);
	waitpid(pid, &status, 0);
	sh->exit_status = WEXITSTATUS(status);
}

void	redirect_out(t_ast *ast, t_shell *sh)
{
	int	fd;

	if (!ast || ast->token->name != REDIR_OUT)
		return ;
	fd = open(ast->right->token->word, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	traverse_tree(ast->left, sh);
}

void	traverse_tree(t_ast *ast, t_shell *sh)
{
	if (!ast)
		return ;
	int copy = dup(STDOUT_FILENO);
	and_or_operators(ast, sh);
	pipe_operator(ast, sh);
	redirect_out(ast, sh);
	command(ast, sh);
	dup2(copy, STDOUT_FILENO);
	close(copy);
	return ;
}
