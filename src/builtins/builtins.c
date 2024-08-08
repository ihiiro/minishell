/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:09:06 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/08 17:56:45 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	builtins_(char *cmd, char **args, t_shell *sh)
{
	if (!ft_strcmp(cmd, "cd"))
		sh->exit_status = cd_(args, &sh->env);
	else if (!ft_strcmp(cmd, "pwd"))
		sh->exit_status = pwd_(sh->env);
	else if (!ft_strcmp(cmd, "env"))
		sh->exit_status = env_(sh->env);
}

void	builtins_exe(char *cmd, t_ast *node, t_shell *sh)
{
	if (!ft_strcmp(cmd, "echo"))
		sh->exit_status = echo_(++node->token->args);
	else if (!ft_strcmp(cmd, "export"))
		sh->exit_status = export_(sh->env, ++node->token->args);
	else if (!ft_strcmp(cmd, "unset"))
		sh->exit_status = unset_(&sh->env, ++node->token->args);
	else if (!ft_strcmp(cmd, "exit"))
		exit_(node->token->args, &sh->env, sh->exit_status);
	builtins_(cmd, ++node->token->args, sh);
}

int	is_builtin(char *str)
{
	char	*builtins[9];
	int		i;

	if (!str)
		return (0);
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "export";
	builtins[3] = "unset";
	builtins[4] = "env";
	builtins[5] = "exit";
	builtins[6] = "pwd";
	builtins[7] = "st";
	builtins[8] = NULL;
	i = -1;
	while (builtins[++i])
		if (!ft_strncmp(str, builtins[i], ft_strlen(builtins[i]) + 1))
			return (1);
	return (0);
}
