#include <assert.h>
#include <libc.h>
#include <stdbool.h>
#include "../include/minishell.h"

/*

Scenario: populating a binary command tree
Given s <-- "echo hi && ls && cat file"
And tree <-- binary
Then populate_bct(tree, s) = 		(&&)
							       /    \
			                 (echo hi)  (ls)
			    			              \
						               (cat file)


*/

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
	printf("\nBINARY-COMMAND-TREE POPULATION TEST-0:\n");
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
	printf("\nBINARY-COMMAND-TREE POPULATION USING populate_bct() TEST-1:\n");
	t_bct	*binary_command_tree;
	binary_command_tree = populate_bct("echo hi && ls && cat file");
	assert(strequal("&&", binary_command_tree->cmd));
	assert(strequal("echo hi", binary_command_tree->left->cmd));
	assert(strequal("ls", binary_command_tree->right->cmd));
	assert(strequal("cat file", binary_command_tree->right->right->cmd));
}