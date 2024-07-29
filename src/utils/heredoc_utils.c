/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 03:29:54 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/29 03:29:56 by mrezki           ###   ########.fr       */
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
