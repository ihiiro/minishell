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

void	builtins_(t_envp **envp, char **strs)
{
	if (!ft_strcmp(strs[0], "cd"))
		cd_(++strs, envp);
	else if (!ft_strcmp(strs[0], "pwd"))
		pwd_(*envp);
	else if (!ft_strcmp(strs[0], "env"))
		env_(*envp);
	else if (!ft_strcmp(strs[0], "exit"))
		exit_(strs, envp);
}

void	check_builtins(char *str, t_envp **envp)
{
	char	**strs;
	char	**head;
	int		i;

	strs = ft_split(str, " \t");
	head = strs;
	builtins_(envp, strs);
	if (!strs)
		ft_printf(2, "Error: Allocation failed\n");
	if (!strs[0])
		return ;
	if (!ft_strcmp(strs[0], "echo"))
		echo_(++strs);
	else if (!ft_strcmp(strs[0], "export"))
		export_(*envp, ++strs);
	else if (!ft_strcmp(strs[0], "unset"))
		unset_(*envp, ++strs);
	else if (!ft_strcmp(strs[0], "leaks"))
		system("leaks -quiet minishell");
	else
		return (free_split(strs));
	free_split(head);
}

char	*copy_env(char *tmp, char *new_value, char **dirs)
{
	tmp = ft_strdup("/");
	if (!tmp)
		return (free_split(dirs), NULL);
	return (free_split(dirs), free(new_value), tmp);
}
