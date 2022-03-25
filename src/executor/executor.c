#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"
#include "executor.h"
#include "debug.h"

char *three_str_cat(char *s1, char *s2, char *s3)
{
	int		len1 = ft_strlen(s1);
	int		len2 = ft_strlen(s2);
	int		len3 = ft_strlen(s3);
	char	*dest = (char *)malloc(sizeof(char) * (len1 + len2 + len3 + 1));
	int i = 0, j = 0;
	while (s1[i] && i < (len1 + len2 + len3 + 1))
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] && i < (len1 + len2 + len3 + 1))
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	j = 0;
	while (s3[j] && i < (len1 + len2 + len3 + 1))
	{
		dest[i] = s3[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char **ht_to_array(t_hashtable *ht)
{
	int		i;
	int		j;
	char	**env_array;
	t_pair	*pair;

	i = -1;
	j = 0;
	env_array = (char **)malloc(sizeof(char *) * (ht->count + 1));
	while (++i < ht->size)
	{
		pair = ht->table[i];
		while (pair)
		{
			env_array[j] = three_str_cat(pair->key, "=", pair->value);
			j++;
			pair = pair->next;
		}
	}
	env_array[j] = 0;
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
	cur_dir = three_str_cat(cur_dir, "/", command->cmd);
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
		cur_dir = three_str_cat(paths[i], "/", command->cmd);
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

char	**adapt_cmd_args(t_simple_cmd *command)
{
	int i = 0, j = 0;
	char **new = (char **)malloc(sizeof(char *) * (command->args_num + 2));
	new[i] = ft_strdup(command->cmd);
	i++;
	while (i <= command->args_num)
	{
		new[i] = ft_strdup(command->cmd_args[j]);
		i++;
		j++;
	}
	new[i] = 0;
	return (new);
}

void	ft_dup2(t_command_table *table, t_pipex_data *data, int index)
{
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

int	handle_builtin(t_command_table *table, t_pipex_data *data, int index)
{
	if (table->commands[index]->type == CMD_PWD
		|| table->commands[index]->type == CMD_ECHO
		|| table->commands[index]->type == CMD_ENV)
	{
		set_fork_builtin(table, data, index);
		return (1);
	}
	else if (table->commands[index]->type == CMD_EXIT && table->commands_num != 1)
		return (1);
	else if (table->commands[index]->type == CMD_CD
		|| table->commands[index]->type == CMD_EXPORT
		|| table->commands[index]->type == CMD_EXIT
		|| table->commands[index]->type == CMD_UNSET
		|| table->commands[index]->type == CMD_ASSIGNMENT)
	{
		exec_builtin(table, data, index);
		return (1);
	}
	else
		return (0);
}

int	exec_cmd(t_command_table *table, t_pipex_data *data, int index)
{
	pid_t	pid;
	int		status;

	if (handle_builtin(table, data, index))
		return (0);
	if (is_executable(table->commands[index]))
	{
		pid = fork();
		if (pid < 0)
			exit(1);
		if (pid == 0)
			exec_bin(table, data, index);
		close(data->tube1[0]);
		close(data->tube1[1]);
		close(data->tube2[0]);
		close(data->tube2[1]);
		waitpid(pid, &status, 0);
	}
	else
		printf("minishell: command not found: %s\n", table->commands[index]->cmd);
	return (1);
}

int	ft_waitpid(t_pipex_data *data)
{
	int	status;
	int	error_code;

	error_code = 0;
	while (data->count_running_cmds-- > 0)
	{
		printf("here\n");
		waitpid(-1, &status, 0);
		if (status != 0)
			error_code = status;
	}
	return (error_code);
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

int	execute(t_command_table *table) // if table == NULL
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
	printf("%d\n", table->commands_num);
	while (++i < table->commands_num)
	{
		if (pipe(data->tube2) < 0)
			perror_exit("pipe tube2");
		ft_dup2(table, data, i);
		exec_cmd(table, data, i);
		close(data->tube1[0]); // закрываем фдшники, полученные из tube2 в цикле (произойдёт в след. операции)
		close(data->tube1[1]);
		data->tube1[0] = data->tube2[0]; // tube1 присваиваются именно фдшники (не какие-то другие данные) tube2 (что по сути делает pipe, поэтому нам не нужно делать pipe(tube1))
		data->tube1[1] = data->tube2[1];
	}
	// close(data->fd1);
	// close(data->fd2);
	// free data
	// free(child_proc);
	return (ft_waitpid(data));
}
