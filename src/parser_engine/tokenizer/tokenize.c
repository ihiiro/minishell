/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:56:13 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/06/12 18:51:15 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../../include/minishell.h"

static int	is_operator(char *word)
{
	if (word[0] == '&' && word[1] == '&')
		return (1);
	else if (word[0] == '|' && word[1] == '|')
		return (1);
	else if (word[0] == '|')
		return (1);
	else if (word[0] == '>' && word[1] == '>')
		return (1);
	else if (word[0] == '>')
		return (1);
	else if (word[0] == '<' && word[1] == '<')
		return (1);
	else if (word[0] == '<')
		return (1);
	return (0);
}

static char	*operator(char *word)
{
	if (word[0] == '&' && word[1] == '&')
		return (ft_substr("&&", 0, 2));
	else if (word[0] == '|' && word[1] == '|')
		return (ft_substr("||", 0, 2));
	else if (word[0] == '|')
		return (ft_substr("|", 0, 1));
	else if (word[0] == '>' && word[1] == '>')
		return (ft_substr(">>", 0, 2));
	else if (word[0] == '>')
		return (ft_substr(">", 0, 1));
	else if (word[0] == '<' && word[1] == '<')
		return (ft_substr("<<", 0, 2));
	else if (word[0] == '<')
		return (ft_substr("<", 0, 1));
	return (NULL);
}

static void	classify(t_token *token_list)
{
	int	prev_type;

	prev_type = NOTHING_TYPED;
	while (token_list)
	{
		token_list->subtree = NULL;
		if (token_list->word[0] == '(')
			token_list->type = PARA_OPEN;
		else if (token_list->word[0] == ')')
			token_list->type = PARA_CLOSE;
		else if (is_operator(token_list->word))
			token_list->type = OPERATOR;
		else if (prev_type == NOTHING_TYPED)
			token_list->type = COMMAND;
		else if (prev_type == COMMAND)
			token_list->type = ARGUMENT;
		else if (prev_type == ARGUMENT)
			token_list->type = ARGUMENT;
		else if (prev_type == OPERATOR || prev_type == PARA_OPEN)
			token_list->type = COMMAND;
		prev_type = token_list->type;
		token_list = token_list->next;
	}
}

static char	*extract(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !operator(&str[i])
		&& str[i] != '('
		&& str[i] != ')')
		i++;
	return (ft_substr(str, 0, i));
}

static void	append_multi(char *word, t_token **token_list)
{
	int		i;
	char	*str;
	t_token	*node;

	i = 0;
	while (word[i])
	{
		str = operator(&word[i]);
		if (word[i] == '(')
			str = ft_substr("(", 0, 1);
		else if (word[i] == ')')
			str = ft_substr(")", 0, 1);
		else if (!str)
			str = extract(&word[i]);
		node = init_node(str);
		append(node, token_list);
		i += ft_strlen(str);
	}
}

void	tokenize(char **word_list, t_token **token_list)
{
	t_token	*node;

	if (!*word_list)
	{
		classify(*token_list);
		return ;
	}
	append_multi(*word_list, token_list);
	tokenize(word_list + 1, token_list);
}
