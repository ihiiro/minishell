/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:45:07 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/18 11:53:02 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	command_loop(t_envp *envp, char *env[], t_shell sh)
{
	char	*str;
	int		sigint;

	while (1)
	{
		init_signal(&sigint);
		str = readline("$> ");
		if (!str)
			exit_(NULL, &envp);
		while (str[0] == '\0' || is_spaces(str))
		{
			free(str);
			str = readline("$> ");
			if (!str)
				exit_(NULL, &envp);
		}
		if (ft_strlen(str) > 0)
			add_history(str);
		sh.ast = parse(str);
		traverse_tree(sh.ast, &sh);
		if (!ft_strncmp(str, "pid", 4))
			printf("%d\n", getpid());
		free(str);
	}
}

int	main(int argc, char *argv[], char *env[])
{
	t_shell	sh;
	char	*str;

	sh.doc_file = ".here_doc_tmp.txt";
	init_envp(env, &sh.env);
	command_loop(sh.env, env, sh);
	free_envp(sh.env);
	return (0);
}
