#include <stdio.h>
#include <signal.h>
#include <sys/signal.h>
#include <unistd.h>
#include <termios.h>

void	signal_handler(int signum)
{
	if (signum == SIGINT)
		printf("\n");
	if (signum == SIGQUIT)
		return ;
}

void	disable_ctrl_c_echo()
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHO;
	printf("%d %d\n", ECHO, ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

int	main(void)
{
	struct sigaction	sa;

	disable_ctrl_c_echo();
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		perror("Error: cannot handle SIGINT");
	while(1)
	{
		printf("Waiting for signal...\n");
		sleep(1);
	}
	return 0;
}
