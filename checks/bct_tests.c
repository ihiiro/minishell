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


	printf("\n#1 WORD SPLITTER:\n");
	char	*line = "echo && ls || cat .gitignore | less";

	char	**words = ft_split(line, ' ');
	for (int i = 0; words[i]; i++)
		printf("word=%s\n", words[i]);
}