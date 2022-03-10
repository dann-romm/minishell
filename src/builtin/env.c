#include "shell.h"
#include "hashtable.h"

void	ft_env() // receives hash-table with env variables
{
	print_ht(g_shell->env_global);
}
