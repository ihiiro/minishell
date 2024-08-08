/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:15:03 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/08 10:30:26 by yel-yaqi         ###   ########.fr       */
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
	char			*tmp;
	int				start;

	(*i)++;
	start = (*i);
	// while ((var[*i] && ft_isalnum(var[*i])) || var[*i] == '_' || var[*i] == '?')
	// 	(*i)++;
	*i += sh->env_var_ends[sh->ends_arr_index] - 1;
	// printf("[%zu] , [sh->ends_arr_index=%zu]\n", sh->env_var_ends[sh->ends_arr_index], sh->ends_arr_index);
	tmp = expand_single_var(var, sh, start, sh->env_var_ends[sh->ends_arr_index]);
	// sh->ends_arr_index++;
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

	result = ft_strdup("");
	tmp = result;
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	sh->ends_arr_index = 0;
	while (var[i])
	{
		if (var[i] == '$' && indices[j] == 2)
			1 && ((i++) && (j++));
		else if (var[i] == '$')
		{
			if (indices[j] == 1 || indices[j] == 3)
				result = expand_(result, var, &i, sh);
			else
				result = copy_char(&i, var, result);
			j++;
			sh->env_var_ends++;
		}
		else
			result = copy_char(&i, var, result);
	}
	if ((unsigned long)result == (unsigned long)tmp)
		*null_var = 1;
	return (result);
}

char	**check_expand(char **args, t_shell *sh, t_token *token)
{
	int		i;
	int		*is_null;
	int		null_var;
	t_token	*head;
	char	*new;

	i = -1;
	head = token;
	null_var = 0;
	is_null = new_arr(args);
	if (!is_null)
		return (NULL);
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
	args = remove_null_values(args, is_null);
	return (wildcard_expansion(args, head));
}
//
//
// char	**ifs_split(char **args, t_token *head)
// {
// 	int	i;
//
// 	i = 0;
// 	while (args[i])
// 	{
// 		printf("%s %lu\n", args[i], head->expansion_indices[0]);
// 		head = head->next;
// 		i++;
// 	}
// 	return (args);
// }
