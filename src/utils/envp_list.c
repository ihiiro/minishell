/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 23:45:01 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/08 17:58:46 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*hereoc_lim(t_ast *ast)
{
	char	*limiter;
	char	*res;
	size_t	*indices;
	size_t	j;
	int		i;

	limiter = ast->right->token->word;
	indices = ast->right->token->expansion_indices;
	i = 0;
	j = 0;
	res = ft_strdup("");
	while (limiter[i])
	{
		if (limiter[i] == '$' && indices[j] == 2)
		{
			i++;
			j++;
		}
		else if (limiter[i] == '$')
			j++;
		res = copy_char(&i, limiter, res);
	}
	return (res);
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
	if (!ft_strncmp(node->name, "OLDPWD", ft_strlen(node->name) + 1))
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

char	*init_vars(int *i, int *j, char **tmp, char **result)
{
	*i = 0;
	*j = 0;
	*result = ft_strdup("");
	if (!*result)
		return (NULL);
	*tmp = *result;
	return (*tmp);
}
