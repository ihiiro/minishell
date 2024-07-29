/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_balanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 17:38:05 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/07/20 18:44:08 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	skip_to_closing(char *line, int *i, int *sc, int *dc)
{
	char	quote;

	quote = line[*i];
	*i += 1;
	while (line[*i])
	{
		if (line[*i] == quote)
			break ;
		*i += 1;
	}
	if (line[*i] && line[*i] == '\'')
		*sc += 1;
	else if (line[*i] && line[*i] == '"')
		*dc += 1;
}

int	quotes_balanced(char *line)
{
	int		single_count;
	int		double_count;
	int		i;

	single_count = 0;
	double_count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			double_count++;
		if (line[i] == '\'')
			single_count++;
		if (line[i] == '\'' || line[i] == '"')
			skip_to_closing(line, &i, &single_count, &double_count);
		i++;
	}
	if (single_count % 2 != 0 || double_count % 2 != 0)
		return (printf("msh: syntax error {unclosed quotes}\n"), 0);
	return (1);
}
