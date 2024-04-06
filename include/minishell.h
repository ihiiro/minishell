/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:48:14 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/04/06 20:29:53 by yel-yaqi         ###   ########.fr       */
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

t_bct	*populate_bct(char *str);

/* TOKENIZER */

# define CONTROL_OPERATOR 0
# define REDIRECTION_OPERATOR 1
# define COMMAND_PART 2

typedef struct s_token
{
	char	*word;
	int		type;
}			t_token;

#endif