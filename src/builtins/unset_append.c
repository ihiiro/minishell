/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 01:02:45 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/08 05:08:47 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	append_to_env(t_envp **env, char *name, char *value)
{
	char	*new_env;
	char	*tmp;

	tmp = search_env(*env, name);
	new_env = ft_strjoin(tmp, value);
	change_env_value(env, name, new_env);
}
