#include "shell.h"
#include "hashtable.h"

void	ft_env()
{
	print_ht(g_shell->env_global);
}
