/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:45:07 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/29 22:11:35 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	process_commands(t_shell *sh, char *str)
{
	if (check_line(str))
	{
		sh->ast = build_ast(str);
		if (!sh->ast)
		{
			sh->exit_status = 258;
			return (1);
		}
		here_doc(sh->ast, sh);
		if (sh->heredoc_trap == 1)
		{
			sh->heredoc_trap = 0;
			return (1);
		}
		traverse_tree(sh->ast, sh);
		close(sh->stdin_copy);
		sh->stdin_copy = -1;
	}
	return (0);
}

void	command_loop(t_envp *envp, char *str, t_shell sh)
{
	char	*prev_line;

	prev_line = NULL;
	while (1)
	{
		init_signal(&sh.exit_status);
		str = readline(ps1_prompt(search_env(envp, "PWD"),
					search_env(envp, "HOME")));
		if (!str)
			exit_(NULL, &envp);
		if (!prev_line || ft_strncmp(prev_line, str, ft_strlen(prev_line) + 1))
		{
			add_history(str);
			if (ft_strncmp(str, "", 1))
				prev_line = ft_strdup(str);
		}
		if (process_commands(&sh, str))
			continue ;
		free(str);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_shell	sh;
	char	*str;

	(void)argc;
	(void)argv;
	str = NULL;
	sh.stdin_copy = -1;
	init_envp(env, &sh.env);
	command_loop(sh.env, str, sh);
	free_envp(sh.env);
	return (0);
}
