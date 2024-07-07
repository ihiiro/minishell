/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:45:07 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/07 01:03:11 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdlib.h>

void	f(void)
{
	system("leaks -quiet minishell");
}

/*
 * bash_exe: Executes a command in bash. NOTE for tests.
 * Usage: run commandss.
 *
 * @str: user prompt.
 * @env: List of environment variables.
 */

void	bash_exe(char *str, char *env[])
{
	char	*path;
	char	**cmds;
	int		pid;

	cmds = ft_split(str, " \t");
	if (!cmds)
		return ;
	if (!cmds[1])
		return (free_split(cmds));
	path = ft_strjoin("/bin/", cmds[1]);
	if (!ft_strncmp(cmds[0], "run", 4))
	{
		if (!access(path, F_OK))
		{
			pid = fork();
			if (pid == 0)
				execve(path, &cmds[1], env);
			else
				wait(NULL);
		}
	}
	free_split(cmds);
	free(path);
}

void	command_loop(t_envp *envp, char *env[])
{
	char	*str;

	while (1)
	{
		str = readline("$> ");
		if (!str)
		{
			printf("exit\n");
			exit(EXIT_FAILURE);
		}
		while (str[0] == '\0' || is_spaces(str))
		{
			free(str);
			str = readline("$> ");
			if (!str)
				break ;
		}
		if (ft_strlen(str) > 0)
			add_history(str);
		shlvl_check(str, &envp);
		check_builtins(str, &envp);
		bash_exe(str, env);
		free(str);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_envp	*envp;
	char	*str;

	init_envp(env, &envp);
	command_loop(envp, env);
	free_envp(envp);
	return (0);
}
