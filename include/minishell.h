/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:48:14 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/04/06 23:56:41 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* BINARY-COMMAND-TREE */

typedef struct s_bct
{
	char			*cmd;
	struct s_bct	*left;
	struct s_bct	*right;
}				t_bct;

/* TOKENIZER */

# define CONTROL_OPERATOR 0
# define REDIRECTION_OPERATOR 1
# define COMMAND 2
# define ARGUMENT 3

typedef struct s_token
{
	char			*word;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}			t_token;

#endif