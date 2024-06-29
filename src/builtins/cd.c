/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:44:54 by mrezki            #+#    #+#             */
/*   Updated: 2024/06/29 18:44:55 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int main(int argc, char *argv[], char *env[])
{
	// for (int i = 1; i < argc; i++)
		// printf("%d: \"%s\"\n", i, argv[i]);
	char *s[30] = {"-n", "ab", "abdsdf asd	 Ó 	fs", NULL};
	// char *s[3] = {NULL};
	
	// char *h = getenv("HOME");
	char *str;
	while ((str = readline("$> ")))
	{
		char **strs = ft_split(str, " ");
		if (strs[0][0] == 'l' && strs[0][1] == 's'
			&& !strs[0][2])
		{
			int pid = fork();
			if (pid == 0)
			{
				execve("/bin/ls", strs, env);
			}
			else {
				wait(NULL);
				// exit(0);
			}
		}
		if (strs[0][0] == 'c' && strs[0][1] == 'd'
			&& !strs[0][2])
		{
			if (strs[2]) {
				printf("Error: cd: too many arguments\n");
			}
			else {
				if (!access(strs[1], F_OK))
					chdir (strs[1]);
				else {
					printf("Error: cd: no such file of directory\n");
				}
			}
		}
		if (strs[0][0] == 'p' && strs[0][1] == 'w'
			&& strs[0][2] == 'd' && !strs[0][3])
			printf("%s\n", getenv("PWD"));
	}
	// printf("%s\n", h);
	// echo_(s);

	return EXIT_SUCCESS;
}
