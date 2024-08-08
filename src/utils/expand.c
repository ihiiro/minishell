/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:15:03 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/05 04:37:45 by yel-yaqi         ###   ########.fr       */
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
		tmp = ft_substr(var, start + 1, end - (start + 1));
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
	while ((var[*i] && ft_isalnum(var[*i])) || var[*i] == '_' || var[*i] == '?')
		(*i)++;
	tmp = expand_single_var(var, sh, start, *i);
	if (tmp)
		result = ft_strjoin(result, tmp);
	if (!result)
		return (perror("Malloc"), NULL);
	return (result);
}

char	*expand_multiple_vars(char *var, t_shell *sh,
			size_t *indices, int *null_var)
{
	char	*result;
	char	*tmp;
	int		i;
	int		j;

	init_vars(&i, &j, &tmp, &result);
	while (var[i])
	{
		if (var[i] == '$' && indices[j] == 2)
			1 && ((i++) && (j++));
		else if (var[i] == '$')
		{
			if (indices[j] == 3 || indices[j] == 1)
				result = expand_(result, var, &i, sh);
			else
				result = copy_char(&i, var, result);
			j++;
		}
		else
			result = copy_char(&i, var, result);
	}
	*null_var = ((unsigned long)result == (unsigned long)tmp);
	return (result);
}

char	**loop_expand(char **args, t_shell *sh, t_token *token, int *is_null)
{
	char	*new;
	int		i;
	int		null_var;

	i = -1;
	null_var = 0;
	while (args[++i])
	{
		if (ft_strchr(args[i], '$'))
		{
			new = expand_multiple_vars(args[i], sh,
					token->expansion_indices, &null_var);
			if (!new)
				continue ;
			args[i] = new;
		}
		is_null[i] = null_var;
		null_var = 0;
		token = token->next;
	}
	return (args);
}

char	**check_expand(char **args, t_shell *sh, t_token *token)
{
	int		*is_null;

	is_null = new_arr(args);
	if (!is_null)
		return (NULL);
	args = loop_expand(args, sh, token, is_null);
	args = remove_null_values(args, is_null);
	return (wildcard_expansion(args, token));
}
