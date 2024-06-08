/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:42:17 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/06/08 20:30:36 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_ast	*fetch_ast(t_token *tokens)
{
	t_ast	*root;

	root = NULL;
	while (tokens)
	{
		if (tokens->name == PIPE && !root)
			root = tokens->subtree;
		if (tokens->name == AND || tokens->name == OR)
			root = tokens->subtree;
		tokens = tokens->next;
	}
	return (root);
}
