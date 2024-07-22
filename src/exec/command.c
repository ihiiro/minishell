/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:52:22 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/18 11:52:22 by mrezki           ###   ########.fr       */
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
		{
			start = ++i;
			if (var[i] == '?')
				i++;
			while ((var[i] && ft_isalnum(var[i])))
				i++;
			tmp = expand_single_var(var, sh, start, i);
			if (tmp)
				result = ft_strjoin(result, tmp);
		}
		else
		{
			tmp = ft_substr(var, i, 1);
			result = ft_strjoin(result, tmp);
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
	return (args);
}

void	command(t_ast *ast, t_shell *sh)
{
	char	**env;

	if (!ast || ast->token->type != COMMAND)
		return ;
	if (!access(sh->doc_file, F_OK))
		copy_to_stdin(sh->doc_file);
	check_expand(ast->token->args, sh);
	if (is_builtin(ast->token->word))
		builtins_exe(ast->token->word, ast, sh);
	else if (!ft_strncmp(ast->token->word, "./minishell", 12))
		shlvl_check(ast->token->word, &sh->env);
	else if (ast->token->type == COMMAND)
	{
		env = copy_env_to_arr(sh->env);
		sh->exit_status = execute_cmd(ast->token->args, env, sh);
		free_split(env);
	}
}
