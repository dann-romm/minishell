#include "shell.h"

void	exec_builtin(t_command_table *table, t_hashtable *ht)
{
	int	i;

	i = 0;
	while (i < table->commands_num)
	{
		if (ft_strcmp(table->commands[i]->cmd, "cd")
			ft_cd(ht, table->commands[i]);
		if (ft_strcmp(table->commands[i]->cmd, "pwd")
			ft_pwd(ht, table->commands[i]);
		...
		...
		...
	}
}