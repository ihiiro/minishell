/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:48:14 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/04/24 11:17:59 by yel-yaqi         ###   ########.fr       */
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

# define OPERATOR 0
# define COMMAND 1
# define ARGUMENT 2
# define PARA_OPEN 3
# define PARA_CLOSE 4

typedef struct s_token
{
	char			*word;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	*last;
}			t_token;


/* minishell */
t_token	*prioritize(t_token *token_list);

void	tokenize(char **word_list, t_token **token_list);

t_token	*init_node(char *word);

void	append(t_token *node, t_token **list);


/* libft */
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strchr(const char *s, int c);

char	*ft_strdup(const char *s1);

char	**ft_split(char *str, char *charset);

size_t	ft_strlen(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);


#endif