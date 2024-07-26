/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrezki <mrezki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:51:59 by mrezki            #+#    #+#             */
/*   Updated: 2024/07/26 23:14:08 by mrezki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_ast
{
	struct s_token	*token;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct s_envp
{
	struct s_envp	*next;
	char			*name;
	char			*value;
}		t_envp;

typedef struct s_gc
{
	void		*garbage;
	struct s_gc	*next;
}		t_gc;

typedef struct s_token
{
	char			*word;
	t_ast			*subtree;
	int				type;
	int				name;
	char			**args;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	*last;
}			t_token;

typedef struct s_shell
{
	char			*doc_file;
	int				exit_status;
	int				stdin_copy;
	t_envp			*env;
	t_ast			*ast;
}		t_shell;

#endif // !STRUCTS_H
