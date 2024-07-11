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

void	builtins_(t_envp **envp, char **strs, t_shell *sh)
{
	if (!ft_strcmp(strs[0], "cd"))
		sh->exit_status = cd_(++strs, envp);
	else if (!ft_strcmp(strs[0], "pwd"))
		sh->exit_status = pwd_(*envp);
	else if (!ft_strcmp(strs[0], "env"))
		sh->exit_status = env_(*envp);
	else if (!ft_strcmp(strs[0], "exit"))
		sh->exit_status = exit_(strs, envp);
}

int	check_builtins(char *str, t_envp **envp, t_shell *sh)
{
	char	**strs;
	char	**head;
	int		i;

	strs = ft_split(str, " \t");
	head = strs;
	if (!strs)
		ft_printf(2, "Error: Allocation failed\n");
	if (!strs[0])
		return (0);
	builtins_(envp, strs, sh);
	if (!ft_strcmp(strs[0], "echo"))
		sh->exit_status = echo_(++strs);
	else if (!ft_strcmp(strs[0], "export"))
		sh->exit_status = export_(*envp, ++strs);
	else if (!ft_strcmp(strs[0], "unset"))
		sh->exit_status = unset_(envp, ++strs);
	else if (!ft_strcmp(strs[0], "leaks"))
		sh->exit_status = system("leaks -quiet minishell");
	free_split(head);
	return (1);
}
