/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:38:36 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/16 21:42:59 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ast	*parse(char *expr) // make static
{
	t_token	*tokens;
	char	**word_list;

	if (!expr)
		return (NULL);
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
	// 
	for (t_token *ptr = tokens; ptr; ptr = ptr->next)
			printf("=%s::%d::%d=\n", ptr->word, ptr->type, ptr->name);
	// 
	return (fetch_ast(tokens));
}

static int	is_incomplete(char *line)
{
	size_t		i;

	if (!line)
		return (0);
	i = ft_strlen(line) - 1;
	while (i != 0 && (line[i] == ' ' || line[i] == '\t'))
		i--;
	if (line[i] == '|' || line[i] == '&' || line[i] == '(')
		return (1);
	return (0);
}

static char	*complete(char *line)
{
	char	*new_line;

	new_line = readline("> ");
	// syntax analyser here!
	free(line);
	return (ft_strjoin(line, new_line));
}

t_ast	*build_ast(void)
{
	char	*line;

	line = readline("mini_bash_clone$ ");
	// syntax analyser should check if parentheses are balanced is not continue building
	while (is_incomplete(line))
		line = complete(line);
	return (parse(line));
}
