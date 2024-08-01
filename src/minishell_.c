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

int	check_line(const char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t')
			return (1);
		str++;
	}
	return (0);
}

int	process_commands(t_shell *sh, char *str)
{
	if (check_line(str))
	{
		add_history(str);
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

char	*ps1_prompt(char *pwd)
{
	char	*prompt;
	char	*tmp;

	tmp = ORANGE"┏━ "RED" 🔥MSH🔥"ORANGE" ━━━━━━━\n┃\e[30m"RED;
	prompt = ft_strjoin(tmp, pwd);
	prompt = ft_strjoin(prompt, "\e[0m"ORANGE"┃\n┗━ $>\e[0m ");
	if (!prompt)
		return (NULL);
	return (prompt);
}

void	command_loop(t_envp *envp, char *str, t_shell sh)
{
	int		sigint;

	while (1)
	{
		init_signal(&sigint);
		str = readline(ps1_prompt(search_env(envp, "PWD")));
		if (!str)
			exit_(NULL, &envp);
		if (process_commands(&sh, str))
			continue ;
		free(str);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	t_shell	sh;
	char	*str;

	str = NULL;
	sh.stdin_copy = -1;
	init_envp(env, &sh.env);
	command_loop(sh.env, str, sh);
	free_envp(sh.env);
	return (0);
}
