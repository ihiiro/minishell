/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:35 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/18 11:52:35 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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