#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"
#include "executor.h"

void	exec_bin(t_command_table *table, t_pipex_data *data, int index)
{
	char	*path;
	char	**args;
	char	**env;

	close(data->tube1[0]);
	close(data->tube1[1]);
	close(data->tube2[0]);
	close(data->tube2[1]);
	path = find_path(table->commands[index]);
	if (!path)
		exit(127);
	args = adapt_cmd_args(table->commands[index]);
	env = ht_to_array(g_shell->env_global);
	execve(path, args, env);
}

int	exec_builtin(t_command_table *table, t_pipex_data *data, int index)
{
	if (table->commands[index]->type == CMD_CD)
		return (ft_cd(table->commands[index]));
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

	else if (table->commands_num == 1)
		return (-1);

	if (table->commands[index]->type == CMD_PWD)
		return (ft_pwd());
	else if (table->commands[index]->type == CMD_ECHO)
		return (ft_echo(table->commands[index]));
	else if (table->commands[index]->type == CMD_ENV)
		return (ft_env());

	return (-1);
}

void	open_files(t_command_table *table, t_pipex_data *data)
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
	if (data->fd1 < 0)
		printf("minishell: %s: %s\n", table->redirect._stdin, strerror(errno));
	if (data->fd2 < 0)
		printf("minishell: %s: %s\n", table->redirect._stdout, strerror(errno));
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
	handle_heredoc(table);
	data->count_running_cmds = 0;
	open_files(table, data);
	if (errno)
	{
		free(data);
		return (0);
	}
	return (data);
}

void	restore_saved_iostream(t_pipex_data *data)
{
	dup2(data->_saved_stdin, STDIN_FILENO);
	dup2(data->_saved_stdout, STDOUT_FILENO);
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
	else if (pid == 0)
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

int	run_cmd_block(t_command_table *table)
{
	t_pipex_data	*data;
	int				child_proc;
	int				i;

	data = init_data(table);
	if (!data || table->commands_num == 0
		|| (table->commands_num == 1 && exec_builtin(table, data, 0) != -1))
		return (errno);
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

int	execute(t_cmd_block *cmd_block)
{
	int	i;
	int	status;

	i = 0;
	status = run_cmd_block(cmd_block[i].table);
	while (cmd_block[i].delimiter != CMDBL_END)
	{
		if (cmd_block[i].delimiter == CMDBL_AND)
		{
			++i;
			if (!status)
				status = run_cmd_block(cmd_block[i].table);
		}
		else if (cmd_block[i].delimiter == CMDBL_OR)
		{
			++i;
			if (status)
				status = run_cmd_block(cmd_block[i].table);
		}
		else
			status = run_cmd_block(cmd_block[++i].table);
	}
	return (status);
}
