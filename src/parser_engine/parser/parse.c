/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:38:36 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/08/05 01:52:02 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_ast	*parse(char *expr)
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
	set_tokens_expansion_indices(tokens);
	remove_quotes(tokens);
	put_args_into_cmd_tokens(tokens);
	tokens = simplify_para(tokens);
	build_list(tokens);
	connect_para(tokens);
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
	if ((line[i] == '|' && line[i - 1] == '|')
		|| (line[i] == '&' && line[i - 1] == '&')
		|| (line[i] == '|'))
		return (1);
	return (0);
}

static char	*complete(char *line)
{
	char		*new_line;
	char		*joint;
	char		*read;
	static int	only_free_first_time;

	read = readline("> ");
	if (!read)
		return (free(read), ft_printf(STDERR_FILENO,
				"msh: syntax error: unexpected end of file\n"), NULL);
	new_line = ft_strjoin(" ", read);
	joint = ft_strjoin(line, new_line);
	free(read);
	only_free_first_time++;
	return (joint);
}

t_ast	*build_ast(char *expr)
{
	int		check;

	check = check_tokens(expr);
	if (!check)
		return (NULL);
	while (check == 2 || is_incomplete(expr))
	{
		expr = complete(expr);
		if (!expr)
			return (NULL);
		check = check_tokens(expr);
		if (!check)
			return (NULL);
	}
	return (parse(expr));
}
