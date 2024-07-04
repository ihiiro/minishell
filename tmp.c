/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 18:44:54 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/03 21:40:14 by mrezki           ###   ########.fr       */
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

void	join_dir(char **tmp, char *str, char **trimmed, char **old)
{
	*tmp = ft_strjoin(str, "/");
	*old = *trimmed;
	*trimmed = ft_strjoin(*trimmed, *tmp);
	free(*tmp);
	free(*old);
}

char	*trim_string(char *str, int size)
{
	char	**dirs;
	char	*trimmed;
	char	*tmp;
	char	*old;
	int		i;

	dirs = ft_split(str, "/");
	i = -1;
	trimmed = NULL;
	while (++i < size)
	{
		if (str[0] == '/' && !i)
		{
			tmp = ft_strjoin("/", dirs[0]);
			trimmed = ft_strjoin(tmp, "/");
			free(tmp);
		}
		else if (i == size - 1)
		{
			old = trimmed;
			trimmed = ft_strjoin(trimmed, dirs[i]);
			free(old);
		}
		else
			join_dir(&tmp, dirs[i], &trimmed, &old);
	}
	printf("%s\n", trimmed);
	return (free_split(dirs), trimmed);
}

int	change_dir(char *pwd, t_envp **env)
{
	char	*dir;
	char	*new_dir;

	new_dir = trim_string(pwd, count_substrs(pwd, "/"));
	if (!access(new_dir, F_OK))
	{
		if (chdir(new_dir) < 0)
			return (free(new_dir), print_error("chdir"));
		change_pwds(env, new_dir, 'd');
	}
	else if (ft_strcmp(new_dir, "-") == 0)
	{
		dir = ft_strdup(search_env(*env, "OLDPWD"));
		if (!dir)
		{
			ft_printf(2, "Error: cd: OLDPWD not set\n");
			return (free(new_dir), 1);
		}
		if (chdir(dir) < 0)
			print_error("chdir");
		change_pwds(env, dir, 'd');
		printf("%s\n", dir);
		free(dir);
	}
	else
		return (free(new_dir), print_error("cd: no such file or directory"));
	return (free(new_dir), 0);
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
