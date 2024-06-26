/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:48:14 by yel-yaqi          #+#    #+#             */
/*   Updated: 2024/06/24 16:36:20 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stddef.h>

/* PARSE ENGINE
					SYNTAX ANALYZER
			 		     |
					WORD SPLITTER
						 |
					 TOKENIZER
					     |
					 PARSER

 */

# define BACKWARDS 0
# define FORWARDS 1

# define NOTHING_TYPED -1
# define OPERATOR 0
# define COMMAND 1
# define ARGUMENT 2
# define PARA_OPEN 3
# define PARA_CLOSE 4
# define AND_OR 5
# define PARA 6

# define NONE -1
# define AND 0
# define OR 1
# define PIPE 2
# define REDIR_OUT 3
# define REDIR_IN 4
# define HERE_DOC 5
# define REDIR_APP 6
# define NOT_OP 7
# define LIMITER 8

struct	s_token;

typedef struct s_ast
{
	struct s_token	*token;
	struct s_ast	*left;
	struct s_ast	*right;
}				t_ast;

typedef struct s_token
{
	char			*word;
	t_ast			*subtree;
	int				type;
	int				name;
	struct s_token	*next;
	struct s_token	*prev;
	struct s_token	*last;
}			t_token;

/* minishell */

void	tokenize(char **word_list, t_token **token_list);

void	append(t_token *node, t_token **list);

void	name_no_redir(t_token *tokens);

void	name_redirections(t_token *tokens);

void	connect_pipelines(t_token *token);

void	connect_para(t_token *tokens);

void	build_list(t_token *start);

void	skip_quoted(char *str, int *i);

void	count_quoted_len(char *str, int *len, char *charset);

t_token	*init_node(char *word);

t_token	*search(t_token *from, int name, int direction);

t_token	*simplify_para(t_token *tokens);

t_ast	*fetch_ast(t_token *tokens);

int		build_pipelines(t_token *token);

int		is_operator(char *word);

/* libft */
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_strchr(const char *s, int c);

char	*ft_strdup(const char *s1);

char	**ft_split(char *str, char *charset);

size_t	ft_strlen(const char *s);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

int		in_charset(char c, char *charset);

#endif