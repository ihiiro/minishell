/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:18 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/18 11:52:19 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	and_or_operators(t_ast *ast, t_shell *sh)
{
	if (ast->token->name == AND)
	{
		traverse_tree(ast->left, sh);
		if (!sh->exit_status)
			traverse_tree(ast->right, sh);
		else
			return ;
	}
	if (ast->token->name == OR)
	{
		traverse_tree(ast->left, sh);
		if (sh->exit_status != 0)
			traverse_tree(ast->right, sh);
		else
			return ;
	}
}
