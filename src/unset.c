#include "shell.h"

void	ft_unset(t_simple_cmd *unset_cmd, t_env *hash_table)
{
	int	i;

	i = 0;
	if (unset_cmd->args_num == 0)
		ft_putstr("unset: not enough arguments\n");
	else
	{
		while (i < unset_cmd->args_num)
		{
			if (find_var(unset_cmd->cmd, hash_table))
				remove_var(unset_cmd->cmd, hash_table);
			i++;
		}
	}
}
