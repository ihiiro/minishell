/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:09:27 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/02 18:09:27 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_envp
{
	char	*name;
	char	*value;
	struct s_envp	*next;
}		t_envp;


/* Built-ins */

void	change_env_value(t_envp **env, char *name, char *new_value);
void	init_envp(char *envp[], t_envp **en);
void	check_builtins(char *str);

int	echo_(char **args);
int	env_(t_envp *head);

char	*search_env(t_envp *env, char *val);

/* Utils */

void	addnode(t_envp **head, char *name, char *value);
void	free_split(char **strs);

t_envp	*create_node(char *name, char *value);

#endif // !BUILTINS_H
