#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"
#include "executor.h"

// s = getenv("PATH"); // покажет значение переменной РАТН

// int is_path_exists(char *str)
// {
// 	struct stat st;
// 	if (stat(str, &st) == 0)
// 		return (1);
// 	return (0);
// }

// char *search_path(char *cmd) // принимает имя команды, а затем ищет каталоги, перечисленные в переменной $PATH, чтобы попытаться найти исполняемый файл команды.
// {
// 	const char	*path = getenv("PATH"); 
// 	char		**all_paths = ft_split(path, ':');
// 	int i = 0, j = 0;
// 	while (all_paths[i])
// 	{
// 		all_paths[i] = ft_strjoin(all_paths[i], "/");
// 		all_paths[i] = ft_strjoin(all_paths[i], cmd);
// 		if (is_path_exists(all_paths[i]))
// 			return (all_paths[i]);
// 		i++;
// 	}
// 	return (0);
// }

//

char *find_path(t_simple_cmd *command)
{
	int i = 0;
	int all = -1;
	char *res = 0;
	char *cur_dir = find_hashtable(g_shell->env_global, "PWD");
	cur_dir = ft_strjoin(cur_dir, command->cmd);
	int cur = access(cur_dir, F_OK);
	if (cur == 0)
	{
		res = cur_dir;
		free(cur_dir);
		return (res);
	}
	char **paths = ft_split(find_hashtable(g_shell->env_global, "PATH"), ':');
	while (paths[i])
	{
		cur_dir = ft_strjoin(paths[i], command->cmd);
		all = access(cur_dir, F_OK);
		if (all == 0)
		{
			res = cur_dir;
			free(cur_dir);
			free_2d_array(paths);
			return (res);
		}
		i++;
	}
	free(cur_dir);
	free_2d_array(paths);
	return (res);
}

int is_executable(t_simple_cmd *command)
{
	int i = 0;
	int all = -1;
	char *path = find_path(command);
	if (!path)
	{
		free(path);
		return (0);
	}
	return (1);
}

int	bin_exec(t_command_table *table, int index,t_pipex_data *data)
{
	if (index == 0)
	{
		if (dup2(data->fd1, 0) < 0 || dup2(data->tube2[1], 1) < 0)
			perror_exit("dup2 86");
	}
	else if (index == table->commands_num - 1)
	{
		if (dup2(data->tube1[0], 0) < 0 || dup2(data->fd2, 1) < 0)
			perror_exit("dup2 91");
	}
	else
	{
		
	}
	return (0);
}

int	exec_cmd(t_command_table *table, int index, t_pipex_data *data)
{
	// set_pipe(table);
	if (is_executable(table->commands[index]))
	{
		if (table->commands[index]->type == CMD_CD)
			return (ft_cd(g_shell->env_global, table->commands[index]));
		if (table->commands[index]->type == CMD_PWD)
			return (ft_pwd(g_shell->env_global));
		if (table->commands[index]->type == 2)
			ft_echo(table->commands[index]->cmd_args, table->commands[index]->args_num); //return
		if (table->commands[index]->type == 6)
			ft_env(g_shell->env_global); //return
		if (table->commands[index]->type == 3)
			ft_export(table->commands[index]); //return
		if (table->commands[index]->type == 5)
			ft_unset(g_shell->env_global, table->commands[index]); //return
		if (table->commands[index]->type == 4)
			ft_exit(table->commands[index]->cmd_args, table->commands[index]->args_num); //return
		else
			bin_exec(table, index, data); //return
	}
	else
		printf("minishell: command not found: %s\n", table->commands[index]->cmd);
	return (1);
}

static void	perror_exit(char *message)
{
	perror(message);
	exit(1);
}

int	ft_waitpid(int i)
{
	int	status;
	int	error_code;

	error_code = 0;
	while (i-- >= 0)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
			error_code = status;
	}
	return (error_code);
}

void open_files(t_command_table *table, t_pipex_data *data)
{
	if (table->redirect._stdin != 0)
		data->fd1 = open(table->redirect._stdin, O_RDONLY);
	else
		data->fd1 = STDIN_FILENO;
	if (table->redirect._stdout != 0)
    	data->fd2 = open(table->redirect._stdout, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		data->fd2 = STDOUT_FILENO;
}

int	execute(t_command_table *table)
{
	int	child_proc;
	int i = -1;
	t_pipex_data *data = (t_pipex_data *)malloc(sizeof(t_cmd_type));

	open_files(table,  data);

	if (table->commands_num == 0)
		return (0);
	while (++i < table->commands_num)
	{
		if (pipe(data->tube2))
			perror_exit("pipe 164");
		child_proc = fork();
		if (child_proc < 0)
			perror_exit(table->commands[i]->cmd);
		if (child_proc == 0)
			exec_cmd(table, i, data);
		close(data->tube1[0]); // закрываем фдшники, полученные из tube2 в цикле (произойдёт в след. операции)
		close(data->tube1[1]);
		data->tube1[0] = data->tube2[0]; // tube1 присваиваются именно фдшники (не какие-то другие данные) tube2 (что по сути делает pipe, поэтому нам не нужно делать pipe(tube1))
		data->tube1[1] = data->tube2[1];
		i++;
	}
	return (ft_waitpid(i));
}
