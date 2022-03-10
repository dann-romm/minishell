#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"

//void	exec_builtin(t_command_table *table, t_hashtable *ht)
//{
//	int	i;

//	i = -1;
//	while (++i < table->commands_num)
//	{
//		if (!ft_strcmp(table->commands[i]->cmd, "cd"))
//			ft_cd(ht, table->commands[i]);
//		if (!ft_strcmp(table->commands[i]->cmd, "pwd"))
//			ft_pwd(ht);
//		if (!ft_strcmp(table->commands[i]->cmd, "echo"))
//			ft_echo(table->commands[i]->cmd_args, table->commands[i]->args_num);
//		if (!ft_strcmp(table->commands[i]->cmd, "env"))
//			ft_env(ht);
//		if (!ft_strcmp(table->commands[i]->cmd, "export"))
//			ft_export(ht, table->commands[i]->cmd_args);
//		if (!ft_strcmp(table->commands[i]->cmd, "unset"))
//			ft_unset(ht, table->commands[i]);
//		if (!ft_strcmp(table->commands[i]->cmd, "exit"))
//			ft_exit(table->commands[i]->cmd_args, table->commands[i]->args_num);;
//	}
//}