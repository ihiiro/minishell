/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var_ends.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:29:56 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/08/08 11:45:48 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

size_t	count_vars(char *expr)
{
	size_t	var_count;

	var_count = 0;
	while (*expr)
	{
		if (*expr == '$')
			var_count++;
		expr++;
	}
	return (var_count);
}

void	set_env_var_ends(char *expr, size_t *var_ends_arr)
{
	size_t	i;
	size_t	end;

	i = 0;
	while (*expr)
	{
		if (*expr == '$')
		{
			end = 0;
			expr++;
			while ((*expr && ft_isalnum(*expr)) || *expr == '_' || *expr == '?')
			{
				expr++;
				end++;
			}
			var_ends_arr[i] = end + 1;
			i++;
		}
		else
			expr++;
	}
}
