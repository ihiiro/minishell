/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_operators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:10:05 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/03 15:07:20 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	name_operators(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->word[0] == '&' && tokens->word[1] == '&')
			tokens->name = AND;
		else if (tokens->word[0] == '|' && tokens->word[1] == '|')
			tokens->name = OR;
		else if (tokens->word[0] == '|')
			tokens->name = PIPE;
		else if (tokens->word[0] == '>' && tokens->word[1] == '>')
			tokens->name = REDIR_APP;
		else if (tokens->word[0] == '<' && tokens->word[1] == '<')
			tokens->name = HERE_DOC;
		else if (tokens->word[0] == '>')
			tokens->name = REDIR_OUT;
		else if (tokens->word[0] == '<')
			tokens->name = REDIR_IN;
		else
			tokens->name = NOT_OP;
		tokens = tokens->next;
	}
}
