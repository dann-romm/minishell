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
	if (execve(find_path(table->commands[0]), adapt_cmd_args(table->commands[0]), ht_to_array(g_shell->env_global)) < 0)
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
	return (1);
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

int	execute(t_command_table *table)
{
	t_pipex_data	*data;
	int				child_proc;
	int				i;

	if (!table)
		return (1);
	i = -1;
	data = (t_pipex_data *)malloc(sizeof(t_pipex_data)); // вынести инициализацию data в отдельную функцию
	if (!data)
		return (1);
	data->count_running_cmds = 0;
	open_files(table, data);
	if (table->commands_num == 0)
		return (0);
	if (pipe(data->tube1))
		perror_exit("pipe tube1");
	while (++i < table->commands_num)
	{
		if (pipe(data->tube2) < 0)
			perror_exit("pipe tube2");
		ft_dup2(table, data, i);
		exec_cmd(table, data, i);

		dup2(data->_saved_stdin, 0);
		dup2(data->_saved_stdout, 1);
		close(data->_saved_stdin);
		close(data->_saved_stdout);

		close(data->tube1[0]); // закрываем фдшники, полученные из tube2 в цикле (произойдёт в след. операции)
		close(data->tube1[1]);
		data->tube1[0] = data->tube2[0]; // tube1 присваиваются именно фдшники (не какие-то другие данные) tube2 (что по сути делает pipe, поэтому нам не нужно делать pipe(tube1))
		data->tube1[1] = data->tube2[1];
	}
	close(data->tube2[0]);
	close(data->tube2[1]);
	if (data->fd1 != 0)
		close(data->fd1);
	if (data->fd2 != 1)
		close(data->fd2);

	return (ft_wait(data));
}
