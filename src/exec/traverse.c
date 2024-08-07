/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:51:22 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/07 12:57:19 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	traverse_tree(t_ast *ast, t_shell *sh)
{
	if (!ast || sh->fork_err)
		return ;
	and_or_operators(ast, sh);
	pipe_operator(ast, sh);
	redirect_out(ast, sh);
	redirect_app(ast, sh);
	redirect_in(ast, sh);
	if (ast->token->name == HERE_DOC)
	{
		copy_to_stdin(sh->doc_files[ast->token->doc_num]);
		traverse_tree(ast->left, sh);
		doc_close(ast, sh, ast->token->doc_num);
	}
	command(ast, sh);
	return ;
}
