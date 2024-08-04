/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:15:03 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/29 23:41:35 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*expand_single_var(char *var, t_shell *sh, int start, int end)
{
	char	*tmp;
	char	*expanded;

	tmp = ft_substr(var, start, end - start);
	if (!tmp)
		return (NULL);
	if (tmp[0] == '?')
	{
		tmp = ft_substr(var, start + 1, end - start);
		expanded = ft_strjoin(ft_itoa(sh->exit_status), tmp);
		return (expanded);
	}
	expanded = search_env(sh->env, tmp);
	return (expanded);
}

char	*expand_(char *result, char *var, int *i, t_shell *sh)
{
	char	*tmp;
	int		start;

	(*i)++;
	start = (*i);
	if (var[*i] == '?')
		(*i)++;
	while ((var[*i] && ft_isalnum(var[*i])) || var[*i] == '_')
		(*i)++;
	tmp = expand_single_var(var, sh, start, *i);
	if (tmp)
		result = ft_strjoin(result, tmp);
	if (!result)
		return (perror("Malloc"), NULL);
	return (result);
}

char	*copy_char(int *i, char *var, char *result)
{
	char	*tmp;

	tmp = ft_substr(var, *i, 1);
	result = ft_strjoin(result, tmp);
	if (!result)
		return (perror("Malloc"), NULL);
	(*i)++;
	return (result);
}

char	*expand_multiple_vars(char *var, t_shell *sh, size_t *indices)
{
	char	*result;
	int		i;
	int		j;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '$')
		{
			if (indices[j])
				result = expand_(result, var, &i, sh);
			else
				result = copy_char(&i, var, result);
			j++;
		}
		else
			result = copy_char(&i, var, result);
	}
	return (result);
}

char	**check_expand(char **args, t_shell *sh, t_token *token)
{
	int		i;
	t_token	*head;
	char	*new;

	i = -1;
	head = token;
	while (args[++i])
	{
		if (ft_strchr(args[i], '$'))
		{
			new = expand_multiple_vars(args[i], sh, token->expansion_indices);
			if (!new)
				continue ;
			args[i] = new;
		}
		token = token->next;
	}
	return (wildcard_expansion(args, head));
}
