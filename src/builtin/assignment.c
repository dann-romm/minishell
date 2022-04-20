#include "shell.h"
#include "libft_funcs.h"

// eq - указатель на место в строке, первый символ '='
int	ft_assignment(t_simple_cmd *cmd)
{
	char	*eq;
	int		i;

	i = -1;
	while (++i < cmd->args_num)
	{
		eq = ft_strchr(cmd->cmd_args[i], '=');
		if (!eq)
			errno = error_manager(ERRT_NOT_FOUND, cmd->cmd_args[i], 127);
		cmd->cmd_args[i][eq++ - cmd->cmd_args[i]] = 0;
		if (check_input(cmd->cmd_args[i]))
			errno = error_manager(ERRT_NOT_FOUND, cmd->cmd_args[i], 127);
		insert_hashtable(g_shell->env_local, cmd->cmd_args[i], eq);
	}
	return (errno);
}
