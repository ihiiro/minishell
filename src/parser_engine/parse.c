/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:38:36 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/09 19:18:00 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*parse(char *expr)
{
	t_token	*tokens;
	char	**word_list;

	tokens = NULL;
	word_list = ft_split(expr, " \t");
	tokenize(word_list, &tokens);
	name_operators(tokens);
	type_files_and_limiters(tokens);
	make_irregular_arguments(tokens);
	put_args_into_cmd_tokens(tokens);
	tokens = simplify_para(tokens);
	build_list(tokens);
	connect_para(tokens);
	return (fetch_ast(tokens));
}
