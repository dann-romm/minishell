#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"

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


int	is_builtin(t_simple_cmd *command)
{
	if (ft_strcmp(command->cmd, "cd"))
		return (1);
	if (ft_strcmp(command->cmd, "echo"))
		return (1);
	if (ft_strcmp(command->cmd, "pwd"))
		return (1);
	if (ft_strcmp(command->cmd, "export"))
		return (1);
	if (ft_strcmp(command->cmd, "unset"))
		return (1);
	if (ft_strcmp(command->cmd, "exit"))
		return (1);
	if (ft_strcmp(command->cmd, "env"))
		return (1);
	return (0);
}

void	execute_cmd(t_simple_cmd *cmd, t_hashtable *ht)
{
	if (!cmd)
		return ;
	//else if (cmd && is_builtin(cmd))
		//exec_builtin(ht, cmd);
	//else
	//	exec_bin(cmd); // for execution of other cmds, not written yet
}