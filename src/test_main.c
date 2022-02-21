#include "shell.h"

// s = getenv("PATH"); // покажет значение переменной РАТН

int is_path_exists(char *str)
{
	struct stat st;
	if (stat(str, &st) == 0)
		return (1);
	return (0);
}

char *search_path(char *cmd) // принимает имя команды, а затем ищет каталоги, перечисленные в переменной $PATH, чтобы попытаться найти исполняемый файл команды.
{
	const char	*path = getenv("PATH"); 
	char		**all_paths = ft_split(path, ':');
	int i = 0, j = 0;
	while (all_paths[i])
	{
		all_paths[i] = ft_strjoin(all_paths[i], "/");
		all_paths[i] = ft_strjoin(all_paths[i], cmd);
		//printf("%s\n", all_paths[i]);
		if (is_path_exists(all_paths[i]))
			return (all_paths[i]);
		i++;
	}
	return (0);
}

void	do_simple_cmd(t_command_table *table)
{
	char			*cmd_path;
	char			**cmd_for_exec;
	int	i = 0, j = 0;

	while (i < 3)
	{
		printf("cmd = %s, args = %s\n", table->commands[i]->cmd, table->commands[i]->cmd_args);
		i++;
	}
	// cmd_for_exec = (char **)malloc(sizeof(sizeof(char *)));
	// cmd_for_exec[0] = command->cmd;
	// cmd_for_exec[1] = command->cmd_args[0];
	// cmd_for_exec[2] = 0;
	// while (i < 2)
	// {
	// 	printf("{%s} ", cmd_for_exec[i]);
	// 	i++;
	// }
	// cmd_path = search_path(command->cmd);
	// printf("cmd path = {%s}\n", cmd_path);
	// execve(cmd_path, cmd_for_exec, table->env);
}

int main(int ac, char **av, char **env)
{
	int32_t 		i;
	int32_t			status;
	pid_t 			child_proc;
	t_command_table *table;
	t_simple_cmd	*cmd1;
	t_simple_cmd	*cmd2;
	// t_simple_cmd	*one_command;

	i = 0;
	status = 0;
	child_proc = 0;
	table = (t_command_table *)malloc(sizeof(t_command_table));
	table->commands = (t_simple_cmd **)malloc(sizeof(t_simple_cmd *));
	cmd1 = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	cmd2 = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	table->commands[0] = cmd1;
	table->commands[1] = cmd2;

	cmd1->cmd = "ls";
	cmd1->cmd_args = "-l";
	cmd2->cmd = "ls";
	cmd2->cmd_args = "-la";
	table->env = env;
	child_proc = fork();
	if (child_proc < 0)
	{
		perror("pipe");
		exit(1);
	}
	if (child_proc == 0)
		do_simple_cmd(table);
	free(table);
	waitpid(-1, &status, 0);
	if (status != 0)
		return (status);
	else
		return (0);
}
