#include "shell.h"

int	set_fork_builtin(t_command_table *table, t_pipex_data *data, int index)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
		exit(exec_builtin(table, data, index));
	else
	{
		close(data->tube1[0]);
		close(data->tube1[1]);
		close(data->tube2[0]);
		close(data->tube2[1]);
		waitpid(pid, &status, 0);
		// if status != 0;
	}
	return (0);
}
