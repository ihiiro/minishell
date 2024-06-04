#include <assert.h>
#include <libc.h>
#include <stdbool.h>
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
	printf("%s\n", root->token->word);
	in_order(root->left);
	in_order(root->right);
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

	printf("	GOOD\n\n");

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

	printf("	GOOD\n\n");

	printf("\n#2 PARSER-BUILD-PIPELINES:\n");
	word_list = ft_split("cmd arg arg arg | cmd arg | cmd | cmd && cmd || cmd | cmd && cmd | cmd", " ");
	tokens = NULL;
	tokenize(word_list, &tokens);
	name_operators(tokens);
	assert(build_pipelines(tokens->last) == 13);
	printf("	GOOD\n\n");
}
