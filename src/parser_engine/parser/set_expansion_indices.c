/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_expansion_indices.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:49:06 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/29 23:01:04 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	set_indices(t_token *token, size_t var_count)
{
	size_t	i;
	size_t	j;
	int		is_quoted_rslt;

	token->expansion_indices = gc_malloc(sizeof(size_t) * var_count, COLLECT);
	ft_memset(token->expansion_indices, 0, sizeof(size_t) * var_count);
	i = 0;
	j = 0;
	while (token->word[i])
	{
		is_quoted_rslt = is_quoted(token->word[i]);
		if ((is_quoted_rslt == '"' || is_quoted_rslt == 0)
			&& token->word[i] == '$')
		{
			token->expansion_indices[j] = 1;
			j++;
		}
		else if (is_quoted_rslt == '\'' && token->word[i] == '$')
			j++;
		i++;
	}
}

void	set_expansion_indices(t_token *token)
{
	size_t	var_count;
	size_t	i;

	var_count = 0;
	i = -1;
	while (token->word[++i])
		if (token->word[i] == '$')
			var_count++;
	if (!var_count)
		return ;
	set_indices(token, var_count);
	// 
	for (size_t i = 0; i < var_count; i++)
		printf("[%zu]", token->expansion_indices[i]);
	printf("\n");
	// 
}

void	set_tokens_expansion_indices(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == LIMITER && (ft_strchr(tokens->word, '\'')
				|| ft_strchr(tokens->word, '"')))
		{
			tokens->expansion_indices = gc_malloc(sizeof(size_t), COLLECT);
			tokens->expansion_indices[0] = 0;
		}
		else
			set_expansion_indices(tokens);
		tokens = tokens->next;
	}
}
