#include "shell.h"

void	ft_env(t_env *hash_table) // receives hash-table with env variables
{
	int i;

	i = 0;
	while (hash_table[i] != 0)
	{
		printf("%s=%s\n", hash_table[i]->data, hash_table[i]->key);
		i++;
	}
}
