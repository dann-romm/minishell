#include "shell.h"

void	ft_unset(t_simple_cmd *unset_cmd, t_env *ht)
{
	int		i;

	i = -1;
	if (unset_cmd->args_num == 0)
		ft_putstr("unset: not enough arguments\n");
	else
	{
		while (++i < unset_cmd->args_num)
		{
			if (find_hashtable(ht, unset_cmd->cmd) != 0)
				delete_hashtable(&ht);
		}
	}
}
