/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:38:36 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/07 12:59:52 by yel-yaqi         ###   ########.fr       */
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
	tokens = simplify_para(tokens);
	build_list(tokens);
	connect_para(tokens);
	printf("\033[0;32mflattened list:\033[0m\n");
	for (t_token *ptr = tokens; ptr; ptr = ptr->next)
		printf("%s ", ptr->word);
	printf("\n\n");
	return (fetch_ast(tokens));
}
