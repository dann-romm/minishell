#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"

// void	exec_cmd(t_command_table *table, t_simple_cmd *command)
// {

// }

// void	set_fork()
// {

// }

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

int	bin_exec(t_simple_cmd *command)
{
	// find path and execute it
	return (0);
}

int	exec_cmd(t_simple_cmd *command)
{
	if (is_executable(command))
	{
		if (command->type == CMD_CD)
			return (ft_cd(g_shell->env_global, command));
		if (command->type == CMD_PWD)
			return (ft_pwd(g_shell->env_global));
		if (command->type == 2)
			ft_echo(command->cmd_args, command->args_num); //return
		if (command->type == 6)
			ft_env(g_shell->env_global); //return
		if (command->type == 3)
			ft_export(command); //return
		if (command->type == 5)
			ft_unset(g_shell->env_global, command); //return
		if (command->type == 4)
			ft_exit(command->cmd_args, command->args_num); //return
		else
			bin_exec(command); //return
	}
	else
		printf("minishell: command not found: %s\n", command->cmd);
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

int	execute(t_command_table *table)
{
	int tube[2];
	int	child_proc;
	int i = -1;

	if (table->commands_num == 0)
		return (0);
	while (++i < table->commands_num)
	{
		if (pipe(tube))
			perror_exit("pipe");
		child_proc = fork();
		if (child_proc < 0)
			exit(1);
			// perror_exit(table->commands[i]); // perror_exit принимает на вход строку (char *), а не (t_simple_cmd *)
		if (child_proc == 0)
			exec_cmd(table->commands[i]);
		close(tube[0]);
		close(tube[1]);
		i++;
	}
	return (ft_waitpid(i));
}
