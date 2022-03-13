#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"

int	is_builtin(t_simple_cmd *some_cmd)
{
	if ((some_cmd->type == CMD_CD, "cd"))
		return (1);
	if ((some_cmd->type == CMD_PWD, "pwd"))
		return (1);
	if ((some_cmd->type == CMD_ECHO, "echo"))
		return (1);
	if ((some_cmd->type == CMD_ENV, "env"))
		return (1);
	if ((some_cmd->type == CMD_EXPORT, "export"))
		return (1);
	if ((some_cmd->type == CMD_UNSET, "unset"))
		return (1);
	if ((some_cmd->type == CMD_EXIT, "exit"))
		return (1);
	return (0);
}

void	exec_builtin(t_simple_cmd *some_cmd)
{
	set_pipe();
	if ((some_cmd->type == CMD_CD, "cd"))
		ft_cd(some_cmd->cmd);
	if ((some_cmd->type == CMD_PWD, "pwd"))
		ft_pwd();
	if ((some_cmd->type == CMD_ECHO, "echo"))
		ft_echo(some_cmd->cmd_args, some_cmd->args_num);
	if ((some_cmd->type == CMD_ENV, "env"))
		ft_env();
	if ((some_cmd->type == CMD_EXPORT, "export"))
		ft_export(some_cmd->cmd);
	if ((some_cmd->type == CMD_UNSET, "unset"))
		ft_unset(some_cmd->cmd);
	if ((some_cmd->type == CMD_EXIT, "exit"))
		ft_exit();
}

void	run_cmd(t_command_table *table) // проходится по каждой команде и запускает соответствующую функцию
{
	int i = 0;
	while (i < table->commands_num)
	{
		if (is_builtin)
			exec_builtin(table->commands[i]);
		else
			exec_cmd(table->commands[i]);
		i++;
	}
}
