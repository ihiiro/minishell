/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:27 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/18 11:52:29 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	here_doc(t_ast *ast, t_shell *sh)
{
	char	*str;
	int		fd;

	if (!ast)
		return ;
	if (ast->token->name == HERE_DOC)
	{
		fd = open(sh->doc_file, O_CREAT | O_TRUNC | O_RDWR, 0664);
		if (fd < 0)
			return (perror("open"));
		sh->stdin_copy = dup(STDIN_FILENO);
		while (1)
		{
			str = readline("> ");
			if (!str)
				return (free(str));
			if (!ft_strncmp(str, ast->right->token->word, ft_strlen(str) + 1))
			{
				return (close(fd), free(str));
			}
			ft_printf(fd, "%s\n", str);
			free(str);
		}
	}
	here_doc(ast->left, sh);
	here_doc(ast->right, sh);
}

void	doc_close(t_ast *ast, t_shell *sh)
{
	if (!ast)
		return ;
	if (!access(sh->doc_file, F_OK))
	{
		dup2(sh->stdin_copy, STDIN_FILENO);
		unlink(sh->doc_file);
		close(sh->stdin_copy);
	}
}

void	copy_to_stdin(char *tmp_file)
{
	int	fd;

	fd = open(tmp_file, O_RDONLY);
	if (fd < 0)
		return (perror("open"));
	dup2(fd, STDIN_FILENO);
}
