/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:27 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/26 23:14:19 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	size_heredocs(t_ast *ast, int *size)
{
	if (!ast || !ast->token)
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

void	fill_doc_files(t_shell *sh)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	size_heredocs(sh->ast, &size);
	if (size > 16)
	{
		print_error("here_doc", "maximum here-document count exceeded");
		exit(EXIT_FAILURE);
	}
	while (i < size)
	{
		sh->doc_files[i] = get_tmp_file_name(i);
		i++;
	}
	sh->doc_files[i] = NULL;
}

void	open_heredocs(t_ast *ast, t_shell *sh, int *i)
{
	char	*str;
	int		fd;

	if (!ast)
		return ;
	if (ast->token->name == HERE_DOC)
	{
		fd = open(sh->doc_files[*i], O_CREAT | O_TRUNC | O_RDWR, 0664);
		(*i)++;
		if (fd < 0)
			return (perror("open"));
		while (1)
		{
			str = readline("> ");
			if (!str)
				return (free(str));
			if (!ft_strncmp(str, ast->right->token->word, ft_strlen(str) + 1))
				return (close(fd), free(str));
			ft_printf(fd, "%s\n", str);
			free(str);
		}
	}
	open_heredocs(ast->left, sh, i);
	open_heredocs(ast->right, sh, i);
}

void	here_doc(t_ast *ast, t_shell *sh)
{
	int	fd;
	int	i;

	if (!ast)
		return ;
	if (sh->stdin_copy == -1)
		sh->stdin_copy = dup(STDIN_FILENO);
	i = 0;
	fill_doc_files(sh);
	open_heredocs(ast, sh, &i);
}
