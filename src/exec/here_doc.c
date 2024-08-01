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

void	heredoc_child_proc(t_shell *sh, char *tmp_file, t_ast *ast, int *i)
{
	char	*str;
	int		fd;

	signal(SIGINT, SIG_DFL);
	fd = open(tmp_file, O_CREAT | O_TRUNC | O_RDWR, 0664);
	(*i)++;
	if (fd < 0)
		return (perror("open"));
	while (1)
	{
		str = readline("> ");
		if (!str)
			exit(0);
		if (!ft_strncmp(str, ast->right->token->word, ft_strlen(str) + 1))
			exit(0);
		ft_printf(fd, "%s\n", expand_in_heredoc(str, sh,
				ast->right->token->expansion_indices[0]));
		free(str);
	}
}

void	open_heredocs(t_ast *ast, t_shell *sh, int *i)
{
	int		pid;

	if (!ast)
		return ;
	if (ast->token->name == HERE_DOC)
	{
		pid = fork();
		if (!pid)
			heredoc_child_proc(sh, sh->doc_files[*i], ast, i);
		else
		{
			signal(SIGINT, SIG_IGN);
			waitpid(pid, &sh->exit_status, 0);
			if (WIFSIGNALED(sh->exit_status))
			{
				write(1, "\n", 1);
				sh->exit_status = 1;
				sh->heredoc_trap = 1;
			}
		}
	}
	open_heredocs(ast->left, sh, i);
	open_heredocs(ast->right, sh, i);
}

void	here_doc(t_ast *ast, t_shell *sh)
{
	int	i;

	if (!ast)
		return ;
	if (sh->stdin_copy == -1)
		sh->stdin_copy = dup(STDIN_FILENO);
	i = 0;
	fill_doc_files(sh);
	open_heredocs(ast, sh, &i);
}
