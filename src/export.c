#include "shell.h"

void	ft_export(t_env *hash_table, char *name, char *value)
{
	int	index;

	index = find_env(hash_table, name, value);
	if (index == 0)
		insert(hash_table, name, value);
	else
	{
		if (hash_table[index]->value)
		{
			free(hash_table[index]->value);
			if (value)
				hash_table[index]->value = ft_strdup(value);
			else
				hash_table[index]->value = 0;
		}
		else
		{
			if (value)
				hash_table[index]->value = ft_strdup(value);
		}
		
	}
}
