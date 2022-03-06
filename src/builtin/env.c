#include "shell.h"
#include "hashtable.h"

void	ft_env(t_hashtable *ht) // receives hash-table with env variables
{
	print_hashtable(ht);
}
