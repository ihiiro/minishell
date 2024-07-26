/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 23:15:03 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/26 23:15:04 by mrezki           ###   ########.fr       */
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
	free(tmp);
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

char	*expand_multiple_vars(char *var, t_shell *sh)
{
	char	*result;
	char	*tmp;
	int		i;
	int		start;

	result = ft_strdup("");
	i = 0;
	while (var[i])
	{
		if (var[i] == '$')
			result = expand_(result, var, &i, sh);
		else
		{
			tmp = ft_substr(var, i, 1);
			result = ft_strjoin(result, tmp);
			if (!result)
				return (perror("Malloc"), NULL);
			i++;
		}
	}
	return (result);
}

char	**check_expand(char **args, t_shell *sh)
{
	int		i;
	char	*new;
	char	*rest;

	i = -1;
	while (args[++i])
	{
		if (ft_strchr(args[i], '$'))
		{
			new = expand_multiple_vars(args[i], sh);
			if (!new)
				return (NULL);
			free(args[i]);
			args[i] = new;
		}
	}
	return (wildcard_expansion(args));
}
