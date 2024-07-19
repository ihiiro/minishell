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

char	*join_rest(char *var, t_envp *env)
{
	char	*tmp;
	char	*new;
	char	*rest;

	tmp = ft_substr(var, first_occur(var, '$') + 1,
			ft_strlen(var) - 1);
	if (!tmp)
		return (perror("Malloc"), NULL);
	new = search_env(env, tmp);
	rest = ft_substr(var, 0, first_occur(var, '$'));
	if (!rest)
		return (perror("Malloc"), NULL);
	new = ft_strjoin(rest, new);
	if (!new)
		return (perror("Malloc"), NULL);
	free(rest);
	return (new);
}

char	*expand_var(char *var, t_envp *env, int has_rest)
{
	char	*tmp;
	char	*new;

	if (has_rest)
		new = join_rest(var, env);
	else
	{
		tmp = ft_substr(var, first_occur(var, '$') + 1,
				ft_strlen(var) - 1);
		if (!tmp)
			return (perror("Malloc"), NULL);
		new = search_env(env, tmp);
	}
	if (!new)
		return (NULL);
	return (new);
}

char	*is_status(char *var, t_shell *sh)
{
	char	*tmp;
	char	*new;
	char	*rest;

	tmp = ft_substr(var, first_occur(var, '$') + 1,
			ft_strlen(var) - 1);
	if (!ft_strncmp(tmp, "?", 2))
	{
		new = ft_itoa(sh->exit_status);
		if (!new)
			return (perror("Malloc"), NULL);
		if (var[0] == '$')
			return (new);
		else
		{
			rest = ft_substr(var, 0, first_occur(var, '$'));
			if (!rest)
				return (perror("Malloc"), NULL);
			new = ft_strjoin(rest, new);
			if (!new)
				return (perror("Malloc"), NULL);
			return (new);
		}
	}
	return (NULL);
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
			if (is_status(args[i], sh))
				new = is_status(args[i], sh);
			else if (args[i][0] == '$')
				new = expand_var(args[i], sh->env, 0);
			else
				new = expand_var(args[i], sh->env, 1);
			free(args[i]);
			args[i] = new;
		}
	}
	return (args);
}

void	command(t_ast *ast, t_shell *sh, int fd)
{
	char	**env;

	if (!ast || ast->token->type != COMMAND)
		return ;
	if (!access(sh->doc_file, F_OK))
		copy_to_stdin(fd, sh->doc_file);
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
