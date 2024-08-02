/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:28:31 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/08 05:08:36 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * check_arg: check whether the argument is numeric.
 * if not exit print error and exit with 255 exit status.
 *
 * @arg: argument passed to exit.
 * @strs: commands.
 * @env: linked list containing environment variables.
 */

void	check_arg(char *arg, char **strs, t_envp *env, short *status)
{
	int	i;

	i = -1;
	if ((arg[0] == '-' || arg[0] == '+') && ft_strlen(arg) != 1)
		i++;
	while (arg[++i])
	{
		if (!ft_isdigit(arg[i]) || (ft_atoi(arg) == -1 && ft_strlen(arg) > 15))
		{
			free_envp(env);
			printf("exit\n");
			printf("minishell: exit: %s: numeric argument required\n", arg);
			free_split(strs);
			exit(255);
		}
	}
	*status = ft_atoi(arg) & 0xFF;
}

/*
 * exit_: exits the shell with optional exit status.
 *
 * @strs: optional exit status.
 * @env: linked list containing environment variables.
 */

void	exit_(char **strs, t_envp **env)
{
	short	exit_status;

	if (!strs)
	{
		free_envp(*env);
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	if (strs[1])
	{
		check_arg(strs[1], strs, *env, &exit_status);
		if (strs[2])
		{
			printf("exit\nminishell: exit: too many arguments\n");
			return ;
		}
	}
	exit_status = 0;
	if (strs[1])
		check_arg(strs[1], strs, *env, &exit_status);
	free_split(strs);
	free_envp(*env);
	printf("exit\n");
	exit(exit_status);
}
