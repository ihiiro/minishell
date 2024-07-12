/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:09:17 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/08 05:08:28 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * env_: Prints all the environment variables.
 *
 * @head: A pointer to the head of a linked list
 * containing environment variables.
 * return: 0 on success.
 */

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

/*
 * search_env: Returns the environment variable value.
 *	NULL if it does not exists.
 *
 * @head: A pointer to the head of a linked list
 * containing environment variables.
 * @val: name of the environment variable to search for.
 */

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

/*
 * search_env_name: Returns the environment variable name.
 *	NULL if it does not exists.
 *
 * @head: A pointer to the head of a linked list
 * containing environment variables.
 * @val: name of the environment variable to search for.
 */

char	*search_env_name(t_envp *env, char *val)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->name, val, ft_strlen(val) + 1) == 0)
			return (env->name);
		env = env->next;
	}
	return (NULL);
}

/*
 * init_envp: Copy the environment variables to a linked list.
 *
 * @envp: List of environment variables.
 * @env: Linked list to copy the environment variables to.
 */

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
	change_env_value(&env, "SHELL", "minishell");
	*en = env;
}

/*
 * change_env_value: chanes the values of an environment variable.
 *
 * @name: name of the environment variable.
 * @new_value: new value of the environment variable.
 */

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
			if (new_value)
				head->value = ft_strdup(new_value);
			else
				head->value = NULL;
			free(tmp);
		}
		head = head->next;
	}
}
