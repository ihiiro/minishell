#include <assert.h>
#include <libc.h>
#include <stdbool.h>
#include <readline/readline.h>
#include "../include/minishell.h"

bool	strequal(char *str0, char *str1)
{
	int	rslt = strcmp(str0, str1);
	if (rslt)
		return (false);
	else
		return (true);
}

void	in_order(t_ast* root)
{
	if (root == NULL)
		return ;
	in_order(root->left);
	in_order(root->right);
	printf("%s\n", root->token->word);
}

int	main(void)
{
	printf("\n#0 TOKENIZER-TYPES:\n");
	char	**word_list = ft_split(" a -l -a&&( b||c -ba | ( f -l	-d -x && g ) )  | d > e	", "	 ");
	t_token	*tokens = NULL;
	tokenize(word_list, &tokens);
	assert(tokens->type == COMMAND);
	assert(tokens->next->type == ARGUMENT);
	assert(tokens->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->type == PARA_OPEN);
	assert(tokens->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->type == PARA_OPEN);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == PARA_CLOSE);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == PARA_CLOSE);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == COMMAND);

	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("\n#1 TOKENIZER-TOKEN-NAMES:\n");
	word_list = ft_split("&& || | > >> << <", " ");
	tokens = NULL;
	tokenize(word_list, &tokens);
	name_operators(tokens);
	assert(tokens->name == AND);
	assert(tokens->next->name == OR);
	assert(tokens->next->next->name == PIPE);
	assert(tokens->next->next->next->name == REDIR_OUT);
	assert(tokens->next->next->next->next->name == REDIR_APP);
	assert(tokens->next->next->next->next->next->name == HERE_DOC);
	assert(tokens->next->next->next->next->next->next->name == REDIR_IN);

	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("\n#2 PARSER-BUILD-PIPELINES:\n");
	// simplify redirections before building pipelines (todo)
	word_list = ft_split("cat arg arg arg | ls arg | grep | wc && awk || cd | echo && less | tr", " ");
	tokens = NULL;
	tokenize(word_list, &tokens);
	name_operators(tokens);
	assert(build_pipelines(tokens->last) == 13);
	connect_pipelines(tokens);

	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("\n#3 PARSER-FETCH-AST:\n");
	assert(fetch_ast(tokens)->token->name == AND);
	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("\n#4 AST-VALIDITY ( build_pipelines() + connect_pipelines() + fetch_ast() ):\n\n");
	word_list = ft_split("cat file0 | grep matchme && ls -la || cd ../..", " ");
	tokens = NULL;
	tokenize(word_list, &tokens);
	name_operators(tokens);
	build_pipelines(tokens->last);
	connect_pipelines(tokens);
	t_ast	*ast = fetch_ast(tokens);
	printf("ROOT->TOKEN=||");
	assert(ast->token->name == OR);
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("ROOT->LEFT->TOKEN=&&");
	assert(ast->left->token->name == AND);
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("ROOT->LEFT->RIGHT->TOKEN=ls");
	assert(strequal(ast->left->right->token->word, "ls"));
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("ROOT->RIGHT->TOKEN=cd");
	assert(strequal(ast->right->token->word, "cd"));
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("ROOT->LEFT->LEFT->TOKEN=|");
	assert(ast->left->left->token->name == PIPE);
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("ROOT->LEFT->LEFT->LEFT->TOKEN=cat");
	assert(strequal(ast->left->left->left->token->word, "cat"));
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n");

	printf("ROOT->LEFT->LEFT->RIGHT->TOKEN=grep");
	assert(strequal(ast->left->left->right->token->word, "grep"));
	printf("\n");
	printf("\033[0;32m	GOOD\033[0m\n\n");

	printf("PROMPT LOOP FOR DYNAMIC TESTING:\n\n");
	while (1)
	{
		tokens = NULL;
		word_list = ft_split(readline("test> "), " ");
		tokenize(word_list, &tokens);
		name_operators(tokens);
		build_pipelines(tokens->last);
		connect_pipelines(tokens);
		in_order(fetch_ast(tokens));
		// for (t_token *ptr = tokens; ptr; ptr = ptr->next)
		// 	printf("%s::%d, ", ptr->word, ptr->type);
		// printf("\n");
	}
}
