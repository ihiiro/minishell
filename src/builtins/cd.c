/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:44:54 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/02 18:09:11 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_error(char *str)
{
	if (str)
		ft_printf(2, "Error: %s\n", str);
	else
		ft_printf(2, "Error\n");
	return (1);
}

int	is_tilde(char *s1, char *s2)
{
	if (!ft_strcmp(s1, "~") && !s2)
		return (1);
	return (0);
}

int	change_dir(char *new_dir, t_envp **env)
{
	char	*dir;

	if (!access(new_dir, F_OK))
	{
		if (chdir(new_dir) < 0)
			return (print_error("chdir"));
		change_pwds(env, new_dir, 'd');
	}
	else if (ft_strcmp(new_dir, "-") == 0)
	{
		dir = ft_strdup(search_env(*env, "OLDPWD"));
		if (!dir)
		{
			ft_printf(2, "Error: cd: OLDPWD not set\n");
			return (1);
		}
		if (chdir(dir) < 0)
			print_error("chdir");
		change_pwds(env, dir, 'd');
		printf("%s\n", dir);
		free(dir);
	}
	else
		return (print_error("cd: no such file or directory"));
	return (0);
}

int	cd_(char **args, t_envp **env)
{
	char	*dir;

	if (!args[0] || is_tilde(args[0], args[1]))
	{
		dir = search_env(*env, "HOME");
		if (!dir)
			return (print_error("HOME is not set"));
		if (chdir(dir) < 0)
			return (print_error("chdir"));
		dir = ft_strdup(dir);
		change_pwds(env, dir, 'h');
		free(dir);
		return (0);
	}
	if (args[1] && args[0])
		return (print_error("cd: too many arguments"));
	else
		return (change_dir(args[0], env));
	return (0);
}

int	count_char(char *str, char h)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == h)
			count++;
		i++;
	}
	return (count);
}

int	first_occur(char *str, char h)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == h)
			return (i);
		i++;
	}
	return (0);
}
