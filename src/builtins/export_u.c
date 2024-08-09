/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:57:17 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/01 15:57:18 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	args_empty(char **args)
{
	while (*args)
	{
		if ((*args)[0])
			return (0);
		args++;
	}
	return (1);
}

void	print_export_vars(t_envp *head)
{
	while (head)
	{
		if (!head->value)
			printf("declare -x %s\n", head->name);
		else if (head->name)
			printf("declare -x %s=\"%s\"\n", head->name, head->value);
		head = head->next;
	}
}

void	add_empty(t_envp **env, char *var)
{
	if (search_env_name(*env, var) == NULL)
		addnode(env, var, NULL);
}

int	character_valid(char c, int is_last, int join_string, char *input)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	if (c == '+' && is_last && join_string
		&& input[first_occur(input, '=') - 1] == '+')
		return (1);
	return (0);
}
