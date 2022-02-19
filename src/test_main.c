#include "shell.h"

// s = getenv("PATH"); // покажет значение переменной РАТН


char *search_path(char *cmd) // принимает имя команды, а затем ищет каталоги, перечисленные в переменной $PATH, чтобы попытаться найти исполняемый файл команды.
{
	const char 		*path = getenv("PATH");

	char **all_paths = ft_split(path, ':');
	int i = 0;
	while (all_paths[i])
	{
		
		// printf("%s\n", ft_strjoin("aaaa", "/bb"));
		ft_strjoin(all_paths[i], "/");
		printf("%s\n", all_paths[i]);
		i++;
	}
}

void	do_simple_cmd(t_command_table *table)
{
	char			*cmd_path;
	t_simple_cmd	*command;

	command = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	command->cmd = "ls";
	cmd_path = search_path(command->cmd);
	// cmd_path = "/bin/ls";
	execve(cmd_path, &command->cmd, table->env);
}

int main(int ac, char **av, char **env)
{
	int32_t 		i;
	int32_t			status;
	pid_t 			child_proc;
	t_command_table *table;
	t_simple_cmd	*command;

	i = 0;
	status = 0;
	child_proc = 0;
	table = (t_command_table *)malloc(sizeof(t_command_table));
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
