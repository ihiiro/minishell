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
#include <stdlib.h>

t_envp	*setup_basic_env(void)
{
	t_envp	*en;
	char	pwd[1024];

	en = NULL;
	addnode(&en, "OLDPWD", NULL);
	addnode(&en, "SHLVL", "1");
	addnode(&en, "PATH", "/usr/bin:/usr/local/bin:/bin:/use/gnu/bin:.");
	if (getcwd(pwd, sizeof(pwd)))
		addnode(&en, "PWD", pwd);
	return (en);
}

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

	env_copy = gc_malloc(sizeof(char *) * (env_len(env) + 1), 1);
	if (!env_copy)
		print_error("Malloc", NULL);
	i = 0;
	while (env)
	{
		if (env->value)
		{
			tmp = ft_strjoin(env->name, "=");
			if (!tmp)
				return (NULL);
			env_copy[i] = ft_strjoin(tmp, env->value);
			if (!env_copy[i])
				return (NULL);
		}
		else
			env_copy[i] = ft_strdup(env->name);
		i++;
		env = env->next;
	}
	return (env_copy[i] = NULL, env_copy);
}

char	*shlvl_new_value(t_envp *env)
{
	char	*new_shlvl;
	int		shell_level;

	shell_level = ft_atoi(search_env(env, "SHLVL"));
	new_shlvl = ft_itoa(++shell_level);
	if (!new_shlvl)
		return (perror("Malloc"), NULL);
	return (new_shlvl);
}

/*
 * shlvl_check: Recursively call the program,
 * and updates SHLVL accoridngly.
 *
 * @str: user prompt.
 * @env: list of environment variables.
 */

void	shlvl_check(char *str, t_envp **env, t_shell *sh)
{
	char	**args;
	char	**envp;
	char	*new_shlvl;
	int		pid;

	new_shlvl = shlvl_new_value(*env);
	change_env_value(env, "SHLVL", new_shlvl);
	args = ft_split(str, " \t");
	if (!args)
		return (perror("Malloc"));
	envp = copy_env_to_arr(*env);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		execve("./minishell", &args[1], envp);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &sh->exit_status, 0);
	sh->exit_status = WEXITSTATUS(sh->exit_status);
}
