/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:01:14 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/29 19:01:15 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * echo_: Mimics the behavior of echo command.
 * args: list of arguments passed to the function.
 * -n: option to remove the trailing newline.
 *  return: 0 on success, >0 if an error occurs.
 */

int	echo_(char **args)
{
	int	n_flag;
	int	i;

	n_flag = 0;
	i = -1;
	if (!args[0])
		return (ft_printf(1, "\n"), 0);
	if (args[0][0] == '-' && args[0][1] == 'n'
		&& !args[1])
		return (0);
	if (args[0][0] == '-' && args[0][1] == 'n'
		&& !args[0][2])
		(1 && (n_flag = 1) && i++);
	while (args[++i])
		printf("%s ", args[i]);
	if (!n_flag)
		printf("\n");
	return (0);
}
