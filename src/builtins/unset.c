/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:28:42 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/08 05:08:50 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * only_chars: Checks if the string contains only chracters and numbers.
 *
 * @str: String to check.
 *
 * return: 0 if not true.
 *	1 if true.
 */

int	only_chars(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/*
 * remove_node_mid: removes a node from the middle of the linked list.
 *
 * @tmp: Current environment variable.
 * @prev: Previous environment variable.
 * @position: position of the variable.
 * @i: index of the node.
 */

void	remove_node_mid(t_envp **tmp, t_envp **prev, int *i, int position)
{
	if (*i == position - 1 && *tmp)
	{
		(*prev)->next = (*tmp)->next;
		(*tmp) = NULL;
	}
	else
	{
		*prev = *tmp;
		if (*prev == NULL)
		{
			*i = -1;
			return ;
		}
		*tmp = (*tmp)->next;
	}
}

/*
 * remove_node: removes a node from the linked list.
 *
 * @env: Linked list containing environment variables.
 * @name: name of the environment variable.
 * @position: position of the variable.
 */

void	remove_node(t_envp **env, int position)
{
	t_envp	*tmp;
	t_envp	*prev;
	int		i;

	i = 0;
	tmp = *env;
	prev = *env;
	while (i < position)
	{
		if (i == 0 && position == 1)
		{
			*env = (*env)->next;
			tmp = NULL;
		}
		else
			remove_node_mid(&tmp, &prev, &i, position);
		if (i < 0)
			break ;
		i++;
	}
}

/*
 * node_position: Gets the position of the variable in the environment variables.
 *
 * @env: Linked list containing environment variables.
 * @name: environment variable name.
 *
 * return: position of the variable.
 *	-1 in case of failure.
 */

int	node_position(t_envp *env, char *name)
{
	t_envp	*head;
	int		i;

	i = 1;
	head = env;
	while (head)
	{
		if (!ft_strcmp(name, head->name))
			return (i);
		i++;
		head = head->next;
	}
	return (-1);
}

/*
 * unset_: Removes environment variable.
 *
 * @env: Linked list containing environment variables.
 * @args: List of arguments to remove from the environment variables.
 *
 * return: 0 on success.
 *	1 on failure.
 */

int	unset_(t_envp **env, char **args)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (args[i])
	{
		if (!only_chars(args[i]))
		{
			ft_printf(2,
				"Error: unset: '%s' not a valid identifier\n", args[i]);
			err = 1;
		}
		if (search_env_name(*env, args[i]) != NULL)
			remove_node(env, node_position(*env, args[i]));
		i++;
	}
	if (err)
		return (1);
	return (0);
}
