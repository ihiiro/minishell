/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:45:07 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/29 18:45:08 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	f(void)
{
	system("leaks -quiet minishell");
}

void	bash_exe(char *str, char *env[])
{
	char	*path;
	char	**cmds;
	char	**tmp;
	int		pid;

	cmds = ft_split(str, " \t");
	if (!cmds)
		return ;
	tmp = cmds;
	if (!cmds[1])
		return ;
	path = ft_strjoin("/bin/", cmds[1]);
	if (!ft_strncmp(cmds[0], "run", 4))
	{
		if (!access(path, F_OK))
		{
			pid = fork();
			if (pid == 0)
				execve(path, cmds + 1, env);
			else
				wait(NULL);
		}
	}
	free(path);
	free_split(tmp);
}

int	main(int argc, char *argv[], char *env[])
{
	t_envp	*envp;
	char	*str;

	atexit(f);
	init_envp(env, &envp);
	while (1)
	{
		str = readline("$> ");
		if (!str)
			break ;
		while (str[0] == '\0')
		{
			free(str);
			str = readline("$> ");
			if (!str)
				break ;
		}
		if (ft_strlen(str) > 0)
			add_history(str);
		check_builtins(str, &envp);
		bash_exe(str, env);
		free(str);
	}
	free_envp(envp);
	return (0);
}
