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
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	sh;
	char	*str;

	sh.env = envp;
	while (1)
	{
		str = readline("$> ");
		if (!str)
			break ;
		check_builtins(str);
	}
	return (0);
}
