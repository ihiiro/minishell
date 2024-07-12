/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 18:09:27 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/08 05:09:18 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_envp
{
	struct s_envp	*next;
	char			*name;
	char			*value;
}		t_envp;

/* Built-ins */

void	change_env_value(t_envp **env, char *name, char *new_value);
void	append_to_env(t_envp **env, char *name, char *value);
void	change_pwds(t_envp **env, char *pwd, char home);
void	shlvl_check(char *str, t_envp **env);
void	init_envp(char *envp[], t_envp **en);
void	exit_(char **strs, t_envp **env);

int		export_(t_envp *env, char **args);
int		unset_(t_envp **env, char **args);
int		cd_(char **args, t_envp **env);
int		is_spaces(char *str);
int		echo_(char **args);
int		env_(t_envp *head);
int		pwd_(t_envp *env);

char	*search_env_name(t_envp *env, char *val);
char	*search_env(t_envp *env, char *val);
char	*add_dir(char *pwd, char *dir);

/* Utils */

void	addnode(t_envp **head, char *name, char *value);
void	free_split(char **strs);
void	free_envp(t_envp *head);

int		first_occur(char *str, char h);
int		count_char(char *str, char h);
int		is_tilde(char *s1, char *s2);
int		count_dots(char **dirs);
int		print_error(char *str);

t_envp	*create_node(char *name, char *value);

#endif // !BUILTINS_H
