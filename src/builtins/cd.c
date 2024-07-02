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
		{
			tmp = head->value;
			if (home == 'h' || pwd[0] == '/')
				new_value = ft_strdup(pwd);
			else
			{
				new_value = ft_strjoin(head->value, "/");
				if (!new_value)
					return;
				full_path = ft_strjoin(new_value, pwd);
				free(new_value);
				if (!full_path)
					return;
				new_value = full_path;
			}
			if (!new_value)
				return;
			head->value = new_value;
			free(tmp);
		}
		head = head->next;
	}
}

int	is_tilde(char *s1, char *s2)
{
	if (!ft_strcmp(s1, "~") && !s2)
		return (1);
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
	{
		if (!access(args[0], F_OK))
		{
			if (chdir(args[0]) < 0)
				return (print_error("chdir"));
			change_pwds(env, args[0], 'd');
		}
		else if (ft_strcmp(args[0], "-") == 0)
		{
			dir = ft_strdup(search_env(*env, "OLDPWD"));
			if (chdir(dir) < 0)
				print_error("chdir");
			change_pwds(env, dir, 'd');
			printf("%s\n", dir);
			free(dir);
		}
		else
			return (print_error("cd: no such file or directory"));
	}
	return (0);
}

t_envp	*create_node(char *name, char *value)
{
	t_envp	*node;

	node = malloc(sizeof(t_envp));
	if (!node)
		return (ft_printf(2, "Error: Allocation\n"), NULL);
	node->name = ft_strdup(name);
	if (!value)
		node->value = NULL;
	else
		node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

void	addnode(t_envp **head, char *name, char *value)
{
	t_envp	*curr;
	t_envp	*node;

	node = create_node(name, value);
	if (!node)
		return ;
	if (!*head)
		*head = node;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = node;
	}
}

void	free_split(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = -1;
	while (strs[++i])
	{
		free(strs[i]);
		strs[i] = NULL;
	}
	free(strs);
	strs = NULL;
}

int	pwd_(t_envp *env)
{
	t_envp	*envp;
	
	envp = env;
	while (env)
	{
		if (!ft_strncmp(env->name, "PWD", 3))
			printf("%s\n", env->value);
		env = env->next;
	}
	env = envp;
	return (0);
}
void    free_envp(t_envp *head)
{
        t_envp        *tmp;

        while (head != NULL)
        {
                tmp = head->next;
		free(head->value);
		free(head->name);
		free(head);
                head = tmp;
        }
}

void	f()
{
	system("leaks -quiet minishell");
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

int	export_(t_envp *env, char **args)
{
	t_envp	*head;
	char	*name;
	char	*value;
	char	*tname;
	char	*tvalue;

	if (!args[0])
	{
		head = env;
		while (head)
		{
			if (!head->value)
				printf("declare -x %s\n", head->name);
			else
				printf("declare -x %s=\"%s\"\n", head->name, head->value);
			head = head->next;
		}
	}
	else
	{
		int i = -1;
		while (args[++i])
		{
			if (count_char(args[i], '=') == 0)
				addnode(&env, args[i], NULL);
			else if (args[i][0] == '=')
			{
				ft_printf(2, "Error: export: '%s': not a valid identifier\n", args[i]);
			}
			else if (count_char(args[i], '=') == 1
					&& args[i][ft_strlen(args[i]) - 1] == '=')
				addnode(&env, ft_strtrim(args[i], "="), "");
			else
			{
				tname = ft_substr(args[i], 0, first_occur(args[i], '='));
				tvalue = ft_substr(args[i], first_occur(args[i], '=') + 1, ft_strlen(args[i]));
				name = ft_strdup(tname);
				value = ft_strdup(tvalue);
				free(tname);
				free(tvalue);
				if (search_env(env, name) != NULL)
					change_env_value(&env, name, value);
				else
					addnode(&env, name, value);
				free(name);
				free(value);
			}
		}
	}
	return (0);
}
/*
 * export: lists env.
 * export var=value: sets var to value, in env and export.
 * export var: sets var with no value only in export.
 * export var=: sets var with empty string in both env and export.
 * export var====" sets var with "===" in value.
 */

int main(int argc, char *argv[], char *env[])
{
	// char *h = getenv("HOME");
	char *str;
	char ** tmp;
	atexit(f);
	t_envp	*envp;

	envp = NULL;
	init_envp(env, &envp);
	while ((str = readline("$> ")))
	{
		char **strs = ft_split(str, " ");
		if ((!ft_strcmp(strs[0], "ls")))
		{
			int pid = fork();
			if (pid == 0)
				execve("/bin/ls", strs, env);
			else
				wait(NULL);
		}
		if (!ft_strcmp(strs[0], "cd"))
		{
			tmp = strs+1;
			cd_(tmp, &envp);
		}
		else if (!ft_strcmp(strs[0], "pwd"))
			pwd_(envp);
		else if (!ft_strcmp(strs[0], "env"))
			env_(envp);
		else if(ft_strcmp(strs[0], "exit") == 0)
			exit(EXIT_SUCCESS);
		else if (!ft_strcmp(strs[0], "export"))
		{
			tmp = strs + 1;
			export_(envp, tmp);
		}
		else if (!ft_strcmp(strs[0], "bash"))
			system("bash");
		free_split(strs);
		free(str);
	}
	free_envp(envp);
	// printf("%s\n", h);
	// echo_(s);

	return EXIT_SUCCESS;
}
