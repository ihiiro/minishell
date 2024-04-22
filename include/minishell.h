/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:48:14 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/04/22 16:34:38 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stddef.h>

/* BINARY-COMMAND-TREE */

typedef struct s_bct
{
	char			*cmd;
	struct s_bct	*left;
	struct s_bct	*right;
}				t_bct;

/* PARSE ENGINE
					SYNTAX ANALYZER
			 		     |
					WORD SPLITTER
						 |
					 TOKENIZER
					     |
					 PRIORITIZER

 */

# define CONTROL_OPERATOR 0
# define REDIRECTION_OPERATOR 1
# define COMMAND 2
# define ARGUMENT 3
# define PARA_OPEN 4
# define PARA_CLOSE 5

typedef struct s_token
{
	char			*word;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}			t_token;


/* minishell */
t_token	*prioritize(t_token *token_list);

t_token	*tokenize(char **word_list);


/* libft */
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strchr(const char *s, int c);

char	*ft_strdup(const char *s1);

char	**ft_split(char const *s, char c);

size_t	ft_strlen(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);


#endif