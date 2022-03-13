#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"

void	exec_cmd(t_command_table *table, t_simple_cmd *command)
{

}

void	set_fork()
{

}

void	check_cmd(t_command_table *table, t_simple_cmd *command)
{
	int	i;
	i = -1;
	while (++i < table->commands_num)
	{
		if (command->type == CMD_CD)
			ft_cd(g_shell->env_global, table->commands[i]);
		if (command->type == CMD_PWD)
			ft_pwd(g_shell->env_global);
		if (command->type == 2)
			ft_echo(table->commands[i]->cmd_args, table->commands[i]->args_num);
		if (command->type == 6)
			ft_env(g_shell->env_global);
		if (command->type == 3)
			ft_export(table->commands[i]);
		if (command->type == 5)
			ft_unset(g_shell->env_global, table->commands[i]);
		if (command->type == 4)
			ft_exit(table->commands[i]->cmd_args, table->commands[i]->args_num);
		else
			exec_cmd(table, command);
	}
}

void	execute(t_command_table *table)
{
	int i = 0;
	if (table->commands_num == 1)
		check_cmd(table, table->commands[0]);
	else
	{
		while (i < table->commands_num)
		{
			pipe()
		}
	}
}
