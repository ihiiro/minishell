#include <assert.h>
#include <libc.h>
#include <stdbool.h>
#include "../include/minishell.h"

/*

Scenario: populating a binary command tree
Given s <-- "echo hi && ls"
And tree <-- binary
Then tree = 		(&&)
					/    \
			   (echo hi)  (ls)


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
	t_bct	*bct;

	assert(strequal("&&", bct->cmd));
	assert(strequal("echo hi", bct->left->cmd));
	assert(strequal("ls", bct->right->cmd));
}