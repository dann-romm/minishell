#include "shell.h"
#include "libft_funcs.h"

#include "debug.h"

int	ft_assignment(t_simple_cmd *cmd)
{
	char	*eq;
	int		i;

	i = -1;
	while (++i < cmd->args_num)
	{
		if (check_input(cmd->cmd_args[i]))
			errno = error_manager(ERRT_CMD_NOT_FOUND, cmd->cmd_args[i], 127);
		else
		{
			eq = ft_strchr(cmd->cmd_args[i], '=');
			if (eq)
			{
				cmd->cmd_args[i][eq++ - cmd->cmd_args[i]] = 0;
				insert_hashtable(g_shell->env_local, cmd->cmd_args[i], eq);
			}
			else
				insert_hashtable(g_shell->env_local, cmd->cmd_args[i], "");
		}
	}
	return (errno);
}
