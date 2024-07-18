/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:44 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/18 11:51:45 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

void	second_child(t_ast *ast, t_shell *sh, int *fd, int *status);
void	here_doc(t_ast *ast, t_shell *sh, int *fd);
void	doc_close(t_ast *ast, t_shell *sh, int fd);
void	and_or_operators(t_ast *ast, t_shell *sh);
void	command(t_ast *ast, t_shell *sh, int fd);
void	pipe_operator(t_ast *ast, t_shell *sh);
void	redirect_out(t_ast *ast, t_shell *sh);
void	redirect_app(t_ast *ast, t_shell *sh);
void	redirect_in(t_ast *ast, t_shell *sh);

#endif // !EXEC_H
