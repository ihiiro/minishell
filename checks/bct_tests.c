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


int	main(void)
{
	printf("\n#0 BINARY-COMMAND-TREE MANUAL POPULATION:\n");
	t_bct	*bct = malloc(sizeof(t_bct));
	t_bct	*left_child_node = malloc(sizeof(t_bct));
	t_bct	*right_child_node = malloc(sizeof(t_bct));
	bct->cmd = "&&";
	bct->left = left_child_node;
	bct->right = right_child_node;
	bct->left->cmd = "echo hi";
	bct->right->cmd = "ls";
	assert(strequal("&&", bct->cmd));
	printf("	bct->cmd: GOOD\n");
	assert(strequal("echo hi", bct->left->cmd));
	printf("	bct->left->cmd: GOOD\n");
	assert(strequal("ls", bct->right->cmd));
	printf("	bct->right->cmd: GOOD\n\n");


	printf("\n#1 TOKENIZER TYPE:\n");
	char	**word_list = ft_split("a -l -a && (b || c -ba | (f -l -d -x && g)) | d > e", ' ');
	t_token	*tokens = tokenize(word_list);
	assert(tokens->type == COMMAND);
	assert(tokens->next->type == ARGUMENT);
	assert(tokens->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->type == OPERATOR);
	// assert(tokens->next->next->next->next->type == PARA_OPEN);
	assert(tokens->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->next->next->next->next->next->next->type == OPERATOR);
	// assert(tokens->next->next->next->next->next->next->next->next->next->next->type == PARA_OPEN);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == ARGUMENT);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == COMMAND);
	// assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == PARA_CLOSE);
	// assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == PARA_CLOSE);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == COMMAND);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == OPERATOR);
	assert(tokens->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->type == COMMAND);
	printf("	GOOD\n");
}
