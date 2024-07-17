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

void	command(t_ast *ast, t_shell *sh, int fd)
{
	char	**env;

	if (!ast || ast->token->type != COMMAND)
		return ;
	// int copy = dup(STDIN_FILENO);
	// if (fd > 0)
		// dup2(fd, STDIN_FILENO);
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
	// dup2(copy, STDIN_FILENO);
	// close(copy);
	// close(fd);
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
	char  *file;
	int	fd;
	int	fd_out;

	if (!ast || ast->token->name != REDIR_OUT)
		return ;
	file = ast->right->token->word;
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		sh->exit_status = print_error(file, MSG_NOPERM);
		return ;
	}
	fd_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	traverse_tree(ast->left, sh);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}
void	redirect_app(t_ast *ast, t_shell *sh)
{
	char  *file;
	int	fd;
	int	fd_out;

	if (!ast || ast->token->name != REDIR_APP)
		return ;
	file = ast->right->token->word;
	if (access(file, X_OK))
	{
		sh->exit_status = print_error(file, MSG_NOPERM);
		return ;
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	fd_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	traverse_tree(ast->left, sh);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

int file_is_okay(char *file, int *status)
{
	if (access(file, F_OK))
	{
		*status = 1;
		return (print_error(file, MSG_NOFILE), 0);
	}
	return (1);
}

void	redirect_in(t_ast *ast, t_shell *sh)
{
	char  *file;
	int	  fd;
	int	  fd_in;

	if (!ast || ast->token->name != REDIR_IN)
		return ;
	file = ast->right->token->word;
	if (!file_is_okay(file, &sh->exit_status))
		return ;
	fd = open(file, O_RDONLY);
	fd_in = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	traverse_tree(ast->left, sh);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}

void  here_doc(t_ast *ast, t_shell *sh, int *fd)
{
	int fds[2];
	char  *str;

	if (!ast || ast->token->name != HERE_DOC)
		return ;
	if (pipe(fds) < 0)
	{
		perror("pipe");
		return ;
	}
	*fd = fds[0];
	printf("%d %d\n", *fd, fds[0]);
	while (1)
	{
		str = readline("> ");
		if (!str)
		{
			free(str);
			print_error("warning",
				"here-document at line 1 delimited by end-of-file (wanted `end')");
			return ;
		}
		if (!ft_strncmp(str, ast->right->token->word, ft_strlen(str) + 1))
		{
			free(str);
			close(fds[1]);
			traverse_tree(ast->left, sh);
			return ;
		}
		ft_printf(fds[1], "%s\n", str);
		free(str);
	}
}

void	traverse_tree(t_ast *ast, t_shell *sh)
{
	static int fd;

	if (!ast)
		return ;
	and_or_operators(ast, sh);
	pipe_operator(ast, sh);
	redirect_out(ast, sh);
	redirect_app(ast, sh);
	redirect_in(ast, sh);
	here_doc(ast, sh, &fd);
	command(ast, sh, fd);
	return ;
}
