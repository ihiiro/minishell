#include "../include/minishell.h"
#include <sys/signal.h>

void	disable_echo(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcgetattr");
		exit(EXIT_FAILURE);
	}
}

void	signal_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	init_signal(int *sigint)
{
	disable_echo();
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGINT, signal_handler) == SIG_ERR
		|| signal(SIGTSTP, SIG_IGN) == SIG_ERR)
	{
		perror("signal");
		exit(EXIT_FAILURE);
	}
	*sigint = 1;
}
