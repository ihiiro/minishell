/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var_ends.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:29:56 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/08/08 10:30:35 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

/*

set_env_var_ends( expr, arr )
	arr = malloc(var_count)
	loop ( expr )
		if (expr == $)
			arr[i] = end

*/

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

	// char	*expr_start = expr;
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
	// 
	// for (size_t j = 0; j < count_vars(expr_start); j++)
	// 	printf("%zu ends at %zu\n", j, var_ends_arr[j]);
	// printf("\n");
	// 
}
