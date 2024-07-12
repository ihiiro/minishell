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
	size_t	len;
	size_t	i;

	len = env_len(env);
	env_copy = malloc(sizeof(char *) * (len + 1));
	if (!env_copy)
		print_error("Allocation failed");
	i = 0;
	while (i < len)
	{
		tmp = ft_strjoin(env->name, "=");
		if (!tmp)
			return (NULL);
		env_copy[i] = ft_strjoin(tmp, env->value);
		if (!env_copy[i])
			return (NULL);
		free(tmp);
		env = env->next;
		i++;
	}
	env_copy[len] = NULL;
	return (env_copy);
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

	if (!ft_strncmp(str, "./minishell",
			ft_strlen("./minishell") + 1))
	{
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
}
