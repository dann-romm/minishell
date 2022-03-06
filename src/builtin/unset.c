#include "shell.h"
#include "hashtable.h"

void	ft_unset(t_hashtable *ht, t_simple_cmd *unset_cmd)
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
