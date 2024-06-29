#include "../../include/minishell.h"

void	check_builtins(char *str)
{
	char	**args;
	int		i;

	args = ft_split(str, " \t");
	if (!args)
		ft_printf(2, "Error: Allocation failed\n");
	if (ft_strncmp(args[0], "echo", 5) == 0)
		echo_(++args);
}
