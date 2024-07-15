/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 03:59:25 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/08 05:08:25 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

size_t	env_len(t_envp *env)
{
	t_envp	*tmp;
	size_t	len;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

/*
 * copy_env_to_arr: copy environment variables
 * from linked list to an array of strings.
 *
 * @env: linked list containing environment variables.
 *
 * return: copy of env.
 */

char	**copy_env_to_arr(t_envp *env)
{
	char	**env_copy;
	char	*tmp;
	size_t	i;

	env_copy = malloc(sizeof(char *) * (env_len(env) + 1));
	if (!env_copy)
		print_error("Malloc", NULL);
	i = -1;
	while (++i < env_len(env))
	{
		tmp = ft_strjoin(env->name, "=");
		if (!tmp)
			return (free_split(env_copy), NULL);
		if (env->value)
		{
			env_copy[i] = ft_strjoin(tmp, env->value);
			free(tmp);
			if (!env_copy[i])
				return (free_split(env_copy), NULL);
		}
		else
			env_copy[i] = tmp;
		env = env->next;
	}
	return (env_copy[i] = NULL, env_copy);
}

/*
 * shlvl_check: Recursively call the program,
 * and updates SHLVL accoridngly.
 *
 * @str: user prompt.
 * @env: list of environment variables.
 */

void	shlvl_check(char *str, t_envp **env)
{
	char	**args;
	char	**envp;
	char	*new_shlvl;
	int		shell_level;
	int		pid;

	shell_level = ft_atoi(search_env(*env, "SHLVL"));
	new_shlvl = ft_itoa(++shell_level);
	change_env_value(env, "SHLVL", new_shlvl);
	pid = fork();
	args = ft_split(str, " \t");
	envp = copy_env_to_arr(*env);
	if (pid == 0)
		execve("./minishell", &args[1], envp);
	else
		wait(NULL);
	free_split(args);
	free_split(envp);
	free(new_shlvl);
}
