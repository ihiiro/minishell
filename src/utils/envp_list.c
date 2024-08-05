/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:45:01 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/02 23:45:01 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*hereoc_lim(t_ast *ast)
{
	char	*limiter;

	limiter = ast->right->token->word;
	if (ast->right->token->expansion_indices[0]
		== 2)
		limiter = ft_substr(limiter, 1, ft_strlen(limiter) - 1);
	return (limiter);
}

char	*oldpwd_(t_envp *env)
{
	char	*buffer;
	char	*new_value;

	buffer = search_env(env, "PWD");
	if (!buffer)
		new_value = ft_strdup("");
	else
		new_value = ft_strdup(buffer);
	return (new_value);
}

t_envp	*create_node(char *name, char *value)
{
	t_envp	*node;

	node = gc_malloc(sizeof(t_envp), 1);
	if (!node)
		return (ft_printf(2, "Error: Allocation\n"), NULL);
	node->name = ft_strdup(name);
	if (!strncmp(node->name, "OLDPWD", ft_strlen(node->name) + 1))
		node->value = NULL;
	else if (!value)
		node->value = NULL;
	else
		node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	addnode(t_envp **head, char *name, char *value)
{
	t_envp	*curr;
	t_envp	*node;

	node = create_node(name, value);
	if (!node)
		return ;
	if (!*head)
		*head = node;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = node;
	}
}
