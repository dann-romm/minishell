#include "shell.h"

void	ft_assignment(t_simple_cmd *cmd)
{
	insert_hashtable(g_shell->env_local, cmd->cmd_args[0], cmd->cmd_args[1]);
	exit(0);
}
