/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:51:22 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/12 09:51:23 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	traverse_tree(t_ast *ast)
{
	int	count_oper;
	
	count_oper = 0;
	if (!ast)
		return ;
	while (ast)
	{
		printf("%s\n", ast->token->word);
		if (ast->token->name == OR || ast->token->name == AND)
			count_oper++;
		ast = ast->left;
	}
	printf("%d\n", count_oper);
}
