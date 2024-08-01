/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 05:44:16 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/01 05:44:17 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_in_heredoc(char *var, t_shell *sh, int expand_flag)
{
	char	*result;
	int		i;
	int		j;

	result = ft_strdup("");
	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '$')
		{
			if (expand_flag)
				result = expand_(result, var, &i, sh);
			else
				result = copy_char(&i, var, result);
			j++;
		}
		else
			result = copy_char(&i, var, result);
	}
	return (result);
}
