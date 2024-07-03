/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:56:54 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/03 14:07:17 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	build(t_token *token)
{
	if (!token->next->next || (!is_redir_operator(token->next->next)
			&& !is_heredoc_operator(token->next->next)))
		printf("a");
}

void	build_redirections(t_token *tokens)
{
	while (tokens && tokens->type != PARA_OPEN)
	{
		if (is_redir_operator(tokens) || is_heredoc_operator(tokens))
			build(tokens);
		tokens = tokens->prev;
	}
}
