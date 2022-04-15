#include "shell.h"
#include "libft_funcs.h"
#include "signals.h"

void	ft_dup2(t_command_table *table, t_pipex_data *data, int index)
{
	data->_saved_stdin = dup(STDIN_FILENO);
	data->_saved_stdout = dup(STDOUT_FILENO);
	if (index == 0)
	{
		if (dup2(data->fd1, 0) < 0)
			printf("minishell: dup2: %s\n", strerror(errno));
	}
	else
	{
		if (dup2(data->tube1[0], 0) < 0)
			printf("minishell: dup2: %s\n", strerror(errno));
	}
	if (index == table->commands_num - 1)
	{
		if (dup2(data->fd2, 1) < 0)
			printf("minishell: dup2: %s\n", strerror(errno));
	}
	else
	{
		if (dup2(data->tube2[1], 1) < 0)
			printf("minishell: dup2: %s\n", strerror(errno));
	}
}

int	ft_wait(t_pipex_data *data)
{
	int	status;

	if (data->fd1 != 0)
		close(data->fd1);
	if (data->fd2 != 1)
		close(data->fd2);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (data->count_running_cmds-- > 0)
		wait(&status);
	if (WIFEXITED(status))
	{
		if (!status)
			return (0);
		if (WEXITSTATUS(status) == 255)
			return (127);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			return (130);
		else if (WTERMSIG(status) == 3)
			return (131);
		return (WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}
