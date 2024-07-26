/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:51:22 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/26 23:14:32 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	traverse_tree(t_ast *ast, t_shell *sh)
{
	if (!ast)
		return ;
	and_or_operators(ast, sh);
	pipe_operator(ast, sh);
	redirect_out(ast, sh);
	redirect_app(ast, sh);
	redirect_in(ast, sh);
	if (ast->token->name == HERE_DOC)
	{
		traverse_tree(ast->left, sh);
		doc_close(ast, sh);
	}
	command(ast, sh);
	return ;
}
