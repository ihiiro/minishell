/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:01:14 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/08 05:08:22 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <unistd.h>

/*
 * skip_flag: skips argument that contains -n flag.
 *
 * @args: list of arguments passsed to echo.
 * @flag: variable to set flag if it exists.
 *
 * return: index of the first valid argument.
 */

int	skip_flag(char **args, int *flag)
{
	int	i;
	int	j;

	i = 0;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		*flag = 1;
		i++;
	}
	return (i);
}

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
	if (!args[0])
		return (ft_printf(1, "\n"), 0);
	i = skip_flag(args, &n_flag);
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
