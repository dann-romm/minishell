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

int	exec_cmd(t_simple_cmd *command)
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
		bin_cmd(command); //return
	return (1);
}

int is_executable(t_simple_cmd *command)
{
	
	// check in current dir
	// check in every PATH way
	if (!access(path1, F_OK) == -1 && )
		printf("minishell: cd: %s: no such file or directory\n", command);
	else if (access(path1, R_OK) == -1)
			printf("minishell: cd: %s: permission denied\n", command);
		else
			printf("minishell: cd: %s: not a directory\n", cd->cmd_args[0]);
	}
}

int	execute(t_command_table *table)
{
	int i = -1;
	if (table->commands_num > 1)
		set_pipe();
	while (++i < table->commands_num)
	{
		set_fork();
		if (is_executable(table->commands[i]))
			return (exec_cmd(table->commands[i]));
		else
		{
			printf("minishell: command not found: %s\n", table->commands[i]);
			return (1);
		}
	}
}
