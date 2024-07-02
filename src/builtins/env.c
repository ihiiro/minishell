/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:09:17 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/02 18:09:18 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*search_env(t_envp *env, char *val)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->name, val, ft_strlen(val) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	init_envp(char *envp[], t_envp **en)
{
	t_envp	*env;
	char	**vals;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		vals = ft_split(envp[i], "=");
		if (vals[0] && vals[1])
			addnode(&env, vals[0], vals[1]);
		free_split(vals);
		i++;
	}
	*en = env;
}

int	env_(t_envp *head)
{
	while (head)
	{
		if (head->name && head->value)
			printf("%s=%s\n", head->name, head->value);
		head = head->next;
	}
	return (0);
}

void	change_env_value(t_envp **env, char *name, char *new_value)
{
	t_envp	*head;
	char	*tmp;

	head = *env;
	while (head)
	{
		if (ft_strcmp(head->name, name) == 0)
		{
			tmp = head->value;
			head->value = ft_strdup(new_value);
			free(tmp);
		}
		head = head->next;
	}
}
