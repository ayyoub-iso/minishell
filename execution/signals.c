#include "../minishell.h"

int ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = -1;
	while (s[++i])
		write(fd, &s[i], 1);
	return (1);
}

void	sig_hand(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int set_signals(void)
{
    rl_catch_signals = 0;
    signal(SIGINT, sig_hand);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

void	child_sig(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit", 1);
	if (waitpid(-1, NULL, 0) > 0)
		ft_putstr_fd("\n", 1);
}
