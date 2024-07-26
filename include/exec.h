/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:44 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/26 23:14:01 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"
# include <stdio.h>

void	expand_arg_entries(char **args, size_t *entry_i, char *pattern);
void	second_child(t_ast *ast, t_shell *sh, int *fd, int *status);
void	and_or_operators(t_ast *ast, t_shell *sh);
void	pipe_operator(t_ast *ast, t_shell *sh);
void	redirect_out(t_ast *ast, t_shell *sh);
void	redirect_app(t_ast *ast, t_shell *sh);
void	redirect_in(t_ast *ast, t_shell *sh);
void	doc_close(t_ast *ast, t_shell *sh);
void	here_doc(t_ast *ast, t_shell *sh);
void	command(t_ast *ast, t_shell *sh);
void	copy_to_stdin(char *tmp_file);

char	*find_path(char *cmd, char *env[], t_shell *sh, char *path_env);
char	**check_expand(char **args, t_shell *sh);
char	**wildcard_expansion(char **args);

size_t	entries_count(char **args);
size_t	entry_count(char *pattern);

int		entry_pattern_match(const char *entry, const char *pattern);
int		match_suffix(const char *entry, const char *pattern);
int		include_hidden(char first, char *entry);

#endif // !EXEC_H
