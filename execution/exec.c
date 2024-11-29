#include "../minishell.h"

#define PATH "/Users/eel-alao/Library/Python/3.8/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Library/Frameworks/Mono.framework/Versions/Current/Commands:/Users/eel-alao/Library/Python/3.8/bin"

int	ft_putstrs(char *s1, char *s2, char *s3, int fd)
{
	if (s1)
		write(fd, s1, ft_strlen(s1));
	if (s2)
		write(fd, s2, ft_strlen(s2));
	if (s3)
		write(fd, s3, ft_strlen(s3));
	return (1);
}

int	get_path(t_exec *s)
{
	char	**pth;
	int	i;
	char	*tmp;
	char	*cmd;

	(1) && (i = -1, cmd = s->cmd);
	if (ft_strchr(cmd, '/') && access(cmd, X_OK | F_OK) == -1)
		return (perror(cmd), 0);
	pth = ft_split(PATH, ':');
	if (!pth)
		return (0);
	while (pth[++i])
	{
		tmp = ft_strjoin(pth[i], "/");
		(tmp) && (tmp = ft_strjoin(tmp, cmd));
		if (!tmp)
			return (0);
		if (access(tmp, X_OK | F_OK) != -1)
			return (s->cmd = tmp, 1);
	}
	if (i == -2)
		return (1);
	return (ft_putstrs(cmd, ": command not found", "\n", 2), exit(127), 0);
}

int	exec_work(t_exec *head, int *fd)
{
	if (head->next)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
	if (head->fd_in != 0)
	{
		dup2(head->fd_in, 0);
		close(head->fd_in);
	}
	if (head->fd_out != 1)
	{
		dup2(head->fd_out, 1);
		close(head->fd_out);
	}
	if (get_path(head))
		execve(head->cmd, head->opt, get_char_env(NULL, 0));
	perror(head->cmd);
	exit(1);
	return (1);
}

int	wait_child(t_minishell *msh, int in)
{
	int	status;

	while (wait(&status) != -1)
	{
		if (WIFEXITED(status))
			msh->exit_status = WEXITSTATUS(status);
		else
			msh->exit_status = WTERMSIG(status) | 128;
	}
	signal(SIGINT, sig_hand);
	signal(SIGQUIT, SIG_IGN);
	return (dup2(in, 0), close(in), 1);
}

int	innit_exec(t_minishell *msh, int *fd)
{
	signal(SIGINT, child_sig);
	signal(SIGQUIT, child_sig);
	if (msh->p_count - 1 > 0)
		return (pipe(fd));
	return (1);
}

int	exec(t_minishell *msh)
{
	t_exec	*head;
	int		pid;
	int		fd[2];
	int		in;

	in = dup(0);
	head = setup_exec_list(msh->parser, msh);
	if (!head)
		return (close(in), 0);
	while (head)
	{
		if (innit_exec(msh, fd) == -1)
			return (perror("pipe()"), close(in), 0);
		pid = fork();
		if (pid == -1)
			return (perror("fork()"), close(fd[0]), close(fd[1]), dup2(in, 0), close(in), 0);
		(pid == 0) && (exec_work(head, fd));
		if (pid > 0)
		{
			(head->next) && (dup2(fd[0], 0), close(fd[0]), \
							close(fd[1]));
			head = head->next;
		}
	}
	return (wait_child(msh, in), 1);
}

// setup execution list
// open fds for redirections
// check path of the given command
// start a simple execution loop