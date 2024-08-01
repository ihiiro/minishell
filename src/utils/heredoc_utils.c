/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 03:29:54 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/01 05:44:28 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	doc_close(t_ast *ast, t_shell *sh, int i)
{
	if (!ast)
		return ;
	if (!access(sh->doc_files[i], F_OK))
	{
		unlink(sh->doc_files[i]);
		dup2(sh->stdin_copy, STDIN_FILENO);
	}
}

void	copy_to_stdin(char *tmp_file)
{
	int	fd;

	fd = open(tmp_file, O_RDONLY);
	if (fd < 0)
		return (perror("open"));
	if (dup2(fd, STDIN_FILENO) < 0)
		return (close(fd), perror("dup2"));
	close(fd);
}

void	size_heredocs(t_ast *ast, int *size)
{
	if (!ast)
		return ;
	if (ast->token->name == HERE_DOC)
	{
		ast->token->doc_num = *size;
		(*size)++;
	}
	size_heredocs(ast->left, size);
	size_heredocs(ast->right, size);
}

char	*get_tmp_file_name(int i)
{
	char	*num;
	char	*tmp_name;

	num = ft_itoa(i + 69);
	tmp_name = ft_strjoin("/tmp/here_doc_tmp_file", num);
	if (!tmp_name)
		return (perror("Malloc"), NULL);
	return (tmp_name);
}
