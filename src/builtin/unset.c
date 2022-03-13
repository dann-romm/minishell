#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"

void	ft_unset(t_simple_cmd *cmd)
{
	int		i;

	i = -1;
	if (cmd->args_num == 0)
		ft_putstr("unset: not enough arguments\n");
	else
	{
		while (++i < cmd->args_num)
		{
			if (find_hashtable(g_shell->env_global, cmd->cmd_args[0]) != 0)
				remove_hashtable(g_shell->env_global, cmd->cmd_args[0]);
		}
	}
}
