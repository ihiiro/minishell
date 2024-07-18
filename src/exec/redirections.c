/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:38 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/18 11:52:39 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	redirect_out(t_ast *ast, t_shell *sh)
{
	char	*file;
	int		fd;
	int		fd_out;

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

int	file_is_okay(char *file, int *status, int fd)
{
	if (access(file, F_OK))
	{
		*status = 1;
		return (print_error(file, MSG_NOFILE), 0);
	}
	if (fd < 0)
	{
		*status = 1;
		return (print_error(file, MSG_NOPERM), 0);
	}
	return (1);
}

void	redirect_app(t_ast *ast, t_shell *sh)
{
	char	*file;
	int		fd;
	int		fd_out;

	if (!ast || ast->token->name != REDIR_APP)
		return ;
	file = ast->right->token->word;
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!file_is_okay(file, &sh->exit_status, fd))
		return ;
	fd_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	traverse_tree(ast->left, sh);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
}

void	redirect_in(t_ast *ast, t_shell *sh)
{
	char	*file;
	int		fd;
	int		fd_in;

	if (!ast || ast->token->name != REDIR_IN)
		return ;
	file = ast->right->token->word;
	fd = open(file, O_RDONLY);
	if (!file_is_okay(file, &sh->exit_status, fd))
		return ;
	fd_in = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	close(fd);
	traverse_tree(ast->left, sh);
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
}
