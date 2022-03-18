#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"

void	ft_unset(t_simple_cmd *unset_cmd)
{
	int		i;

	i = -1;
	if (unset_cmd->args_num == 0)
		printf("unset: not enough arguments\n");
	else
	{
		while (++i < unset_cmd->args_num)
		{
			if (find_hashtable(g_shell->env_global, unset_cmd->cmd) != 0)
				delete_hashtable(&(g_shell->env_global));
		}
	}
}
