#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"
#include "executor.h"

char **ht_to_array(t_hashtable *ht) // transform it to a function which concatenates 3 strings
{
	int		i;
	int		j;
	char	**env_array;
	t_pair	*pair;

	i = -1;
	j = -1;
	env_array = (char **)malloc(sizeof(char *) * (ht->count + 1));
	while (++i < ht->size)
	{
		pair = ht->table[i];
		while (pair)
		{
			env_array[j] = ft_strjoin(pair->key, "="); // due to inability to free this strjoin make another function
			env_array[j] = ft_strjoin(env_array[j], pair->value);
			j++;
			pair = pair->next;
		}
	}
	ht->table[i] = 0;
	return (env_array);
}

static void	perror_exit(char *message)
{
	perror(message);
	exit(1);
}

char *find_path(t_simple_cmd *command)
{
	int i = 0;
	int all = -1;
	char *res = 0;
	char *cur_dir = find_hashtable(g_shell->env_global, "PWD");
	cur_dir = ft_strjoin(cur_dir, "/"); // memory leak at cur_dir
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
		cur_dir = ft_strjoin(paths[i], "/"); // memory leak at cur_dir
		cur_dir = ft_strjoin(cur_dir, command->cmd);
		all = access(cur_dir, F_OK);
		if (all == 0)
		{
			res = ft_strdup(cur_dir);
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

int	bin_exec(t_command_table *table, int index, t_pipex_data *data)
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
		if(dup2(data->tube1[0], 0) < 0 || dup2(data->tube2[1], 1) < 0)
			perror_exit("dup2 100");
	}
	close(data->tube1[0]);
	close(data->tube1[1]);
	close(data->tube2[0]);
	close(data->tube2[1]);
	printf("bin path -> %s\n", find_path(table->commands[0]));
	// execve(find_path(table->commands[0]), table->commands[0]->cmd_args, g_shell->env_global);
	return (0);
}

int	exec_cmd(t_command_table *table, int index, t_pipex_data *data)
{
	// set_pipe(table);
	if (is_executable(table->commands[index]))
	{
		if (table->commands[index]->type == CMD_CD)
			return (ft_cd(table->commands[index]));
		if (table->commands[index]->type == CMD_PWD)
			return (ft_pwd(g_shell->env_global));
		if (table->commands[index]->type == 2)
			ft_echo(table->commands[index]->cmd_args, table->commands[index]->args_num); //return
		if (table->commands[index]->type == 6)
			ft_env(g_shell->env_global); //return
		if (table->commands[index]->type == 3)
			ft_export(table->commands[index]); //return
		if (table->commands[index]->type == 5)
			ft_unset(table->commands[index]); //return
		if (table->commands[index]->type == 4)
			ft_exit(table->commands[index]->cmd_args, table->commands[index]->args_num); //return
		else
			bin_exec(table, index, data); //return
	}
	else
		printf("minishell: command not found: %s\n", table->commands[index]->cmd);
	return (1);
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
