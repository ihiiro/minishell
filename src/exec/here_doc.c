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

void	here_doc(t_ast *ast, t_shell *sh, int *fd)
{
	char	*str;
	int		copy;

	if (!ast || ast->token->name != HERE_DOC)
		return ;
	*fd = open(".here_doc_tmp.txt", O_CREAT | O_APPEND | O_RDWR, 0664);
	if (*fd < 0)
		return (perror("open"));
	sh->stdin_copy = dup(STDIN_FILENO);
	while (1)
	{
		str = readline("> ");
		if (!str)
			return (free(str));
		if (!ft_strncmp(str, ast->right->token->word, ft_strlen(str) + 1))
		{
			free(str);
			traverse_tree(ast->left, sh);
			return ;
		}
		ft_printf(*fd, "%s\n", str);
		free(str);
	}
}

void	doc_close(t_ast *ast, t_shell *sh, int fd)
{
	if (!ast)
		return ;
	if (!access(sh->doc_file, F_OK))
	{
		dup2(sh->stdin_copy, STDIN_FILENO);
		unlink(sh->doc_file);
		close(sh->stdin_copy);
		close(fd);
	}
}
