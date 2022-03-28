#include "shell.h"
#include "libft_funcs.h"

void	ft_dup2(t_command_table *table, t_pipex_data *data, int index)
{
	data->_saved_stdin = dup(0);
	data->_saved_stdout = dup(1);
	if (index == 0)
	{
		if (dup2(data->fd1, 0) < 0)
			perror_exit("dup2 134");
	}
	else
	{
		if (dup2(data->tube1[0], 0) < 0)
			perror_exit("dup2 139");
	}
	if (index == table->commands_num - 1)
	{
		if (dup2(data->fd2, 1) < 0)
			perror_exit("dup2 144");
	}
	else
	{
		if (dup2(data->tube2[1], 1) < 0)
			perror_exit("dup2 149");
	}
}

int	ft_waitpid(t_pipex_data *data)
{
	int	status;
	int	error_code;

	error_code = 0;
	while (data->count_running_cmds-- > 0)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
			error_code = status;
	}
	return (error_code);
}
