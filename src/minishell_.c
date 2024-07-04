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
		check_builtins(str, &envp);
		free(str);
	}
	free_envp(envp);
	return (0);
}
