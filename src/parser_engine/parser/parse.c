/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 12:38:36 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/20 18:34:14 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

t_ast	*parse(char *expr) // make static
{
	t_token	*tokens;
	char	**word_list;

	if (!expr)
		return (NULL);
	tokens = NULL;
	word_list = ft_split(expr, " \t");
	free(expr);
	tokenize(word_list, &tokens);
	name_operators(tokens);
	type_files_and_limiters(tokens);
	make_irregular_arguments(tokens);
	put_args_into_cmd_tokens(tokens);
	// 
	for (t_token *ptr = tokens; ptr; ptr = ptr->next)
			printf("=%s::%d::%d=\n", ptr->word, ptr->type, ptr->name);
	// 
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
	new_line = ft_strjoin(" ", read);
	joint = ft_strjoin(line, new_line);
	if (!only_free_first_time)
		free(line);
	free(read);
	only_free_first_time++;
	return (joint);
}

t_ast	*build_ast(void)
{
	char	*line;
	int		check;
	int		loop_entered;

	line = readline("mini_bash_clone$ ");
	check = check_tokens(line);
	if (!check)
		return (free(line), NULL);
	loop_entered = 0;
	while (check == 2 || is_incomplete(line))
	{
		line = complete(line);
		check = check_tokens(line);
		if (!check)
			return (NULL);
		loop_entered = 1;
	}
	return (parse(line));
}
