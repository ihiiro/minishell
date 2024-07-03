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

void	check_builtins(char *str, t_envp **envp)
{
	char	**strs;
	char	**head;
	int		i;

	strs = ft_split(str, " \t");
	head = strs;
	if (!strs)
		ft_printf(2, "Error: Allocation failed\n");
	if (!strs[0])
		return ;
	if (!ft_strcmp(strs[0], "echo"))
		echo_(++strs);
	else if (!ft_strcmp(strs[0], "cd"))
		cd_(++strs, envp);
	else if (!ft_strcmp(strs[0], "pwd"))
		pwd_(*envp);
	else if (!ft_strcmp(strs[0], "env"))
		env_(*envp);
	else if (!ft_strcmp(strs[0], "exit"))
		exit(EXIT_SUCCESS);
	else if (!ft_strcmp(strs[0], "export"))
		export_(*envp, ++strs);
	else if (!ft_strcmp(strs[0], "unset"))
		unset_(*envp, ++strs);
	else
	{
		free_split(strs);
		return ;
	}
	free_split(head);
}
