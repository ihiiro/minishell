/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 21:28:38 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/02 21:28:38 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * handle_pwd: Updates the PWD envirement variable.
 *
 * @head: A pointer to the node that has PWD envirement variablel.
 * @pwd: Current working directory.
 * @home: A character representing the home directory (cd, or cd ~), h for home.
 */

void	handle_pwd(char home, char *pwd, t_envp *head)
{
	char	*tmp;
	char	*new_value;
	char	*full_path;

	tmp = head->value;
	if (home == 'h' || pwd[0] == '/')
		new_value = ft_strdup(pwd);
	else
	{
		new_value = ft_strjoin(head->value, "/");
		if (!new_value)
			return ;
		full_path = ft_strjoin(new_value, pwd);
		free(new_value);
		if (!full_path)
			return ;
		new_value = full_path;
	}
	if (!new_value)
		return ;
	head->value = new_value;
	free(tmp);
}

/*
 * change_pwds: Updates the PWD and OLDPWD variables.
 *
 * @env: A pointer to the head of linked list envirement variable.
 * @pwd: Current working directory.
 * @home: A character representing the home directory (cd, or cd ~).
 */

void	change_pwds(t_envp **env, char *pwd, char home)
{
	t_envp	*head;
	char	*tmp;
	char	*new_value;
	char	*full_path;

	head = *env;
	while (head)
	{
		if (ft_strcmp(head->name, "OLDPWD") == 0)
		{
			tmp = head->value;
			new_value = ft_strdup(search_env(*env, "PWD"));
			head->value = new_value;
			free(tmp);
		}
		if (ft_strcmp(head->name, "PWD") == 0)
			handle_pwd(home, pwd, head);
		head = head->next;
	}
}

/*
 * pwd_: Prints the current working directory.
 *
 * @env: A pointer to the head of linked list envirement variable.
 *
 * @return:
 *	0 on success.
 *	1 in case of failure.
 */

int	pwd_(t_envp *env)
{
	while (env)
	{
		if (!ft_strncmp(env->name, "PWD", 3))
		{
			printf("%s\n", env->value);
			return (0);
		}
		env = env->next;
	}
	ft_printf(2, "Error: PWD is not set\n");
	return (1);
}
