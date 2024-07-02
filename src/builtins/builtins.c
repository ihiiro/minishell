/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:09:06 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/02 18:09:08 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_builtins(char *str)
{
	char	**args;
	int		i;

	args = ft_split(str, " \t");
	if (!args)
		ft_printf(2, "Error: Allocation failed\n");
	if (!args[0])
		return ;
	if (ft_strncmp(args[0], "echo", 5) == 0)
		echo_(++args);
}
