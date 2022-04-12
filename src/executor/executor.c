#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"
#include "executor.h"
#include "debug.h"

void	exec_bin(t_command_table *table, t_pipex_data *data, int index)
{
	close(data->tube1[0]);
	close(data->tube1[1]);
	close(data->tube2[0]);
	close(data->tube2[1]);
	if (execve(find_path(table->commands[index]), adapt_cmd_args(table->commands[index]), ht_to_array(g_shell->env_global)) < 0)
		printf("execve");
}

int	exec_builtin(t_command_table *table, t_pipex_data *data, int index)
{
	if (table->commands[index]->type == CMD_CD)
		return (ft_cd(table->commands[index]));
	else if (table->commands[index]->type == CMD_PWD)
		return (ft_pwd());
	else if (table->commands[index]->type == CMD_ECHO)
		return (ft_echo(table->commands[index]));
	else if (table->commands[index]->type == CMD_ENV)
		return (ft_env());
	else if (table->commands[index]->type == CMD_EXPORT)
		return (ft_export(table->commands[index]));
	else if (table->commands[index]->type == CMD_UNSET)
		return (ft_unset(table->commands[index]));
	else if (table->commands[index]->type == CMD_EXIT)
	{
		ft_exit(table->commands[index]->cmd_args, table->commands[index]->args_num);
		return (0);
	}
	else if (table->commands[index]->type == CMD_ASSIGNMENT)
		return (ft_assignment(table->commands[index]));
	return (-1);
}

void open_files(t_command_table *table, t_pipex_data *data) // add << (it's heredoc)
{
	if (table->redirect._stdin != 0)
		data->fd1 = open(table->redirect._stdin, O_RDONLY);
	else
		data->fd1 = STDIN_FILENO;
	if (table->redirect._stdout != 0)
	{
		if (table->redirect.is_stdout_append)
			data->fd2 = open(table->redirect._stdout, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			data->fd2 = open(table->redirect._stdout, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else
		data->fd2 = STDOUT_FILENO;
}

t_pipex_data	*init_data(t_command_table *table)
{
	t_pipex_data	*data;

	data = (t_pipex_data *)malloc(sizeof(t_pipex_data));
	if (!data)
		return (0);
	data->count_running_cmds = 0;
	data->_saved_stdin = -1;
	data->_saved_stdout = -1;
	data->tube1[0] = -1;
	data->tube1[1] = -1;
	data->tube2[0] = -1;
	data->tube2[1] = -1;
	data->limiter = NULL;
	data->count_running_cmds = 0;
	open_files(table, data);
	return (data);
}

void	restore_saved_iostream(t_pipex_data *data)
{
	dup2(data->_saved_stdin, 0);
	dup2(data->_saved_stdout, 1);
	close(data->_saved_stdin);
	close(data->_saved_stdout);
}

int	exec_cmd(t_command_table *table, t_pipex_data *data, int index)
{
	pid_t	pid;

	ft_dup2(table, data, index);
	data->count_running_cmds++;
	pid = fork();
	if (pid == -1) // error
		return (1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (exec_builtin(table, data, index) == -1)
			exec_bin(table, data, index);
		exit(0);
	}
	else
		restore_saved_iostream(data);
	return (0);
}

int	execute(t_command_table *table)
{
	t_pipex_data	*data;
	int				child_proc;
	int				i;

	data = init_data(table);
	if (!data || table->commands_num == 0
		|| (table->commands_num == 1 && exec_builtin(table, data, 0) != -1))
		return (0);
	if (pipe(data->tube1))
		perror_exit("pipe tube1");
	i = -1;
	while (++i < table->commands_num)
	{
		if (pipe(data->tube2) < 0)
			perror_exit("pipe tube2");
		exec_cmd(table, data, i);
		close(data->tube1[0]);
		close(data->tube1[1]);
		data->tube1[0] = data->tube2[0];
		data->tube1[1] = data->tube2[1];
	}
	close(data->tube2[0]);
	close(data->tube2[1]);

	return (ft_wait(data));
}
