/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:28:31 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/07 01:02:30 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * exit_: exits the shell.
 *
 * @strs: commands.
 * @env: linked list containing environment variables.
 */

void	exit_(char **strs, t_envp **env)
{
	free_split(strs);
	free_envp(*env);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
