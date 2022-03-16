#include "shell.h"
#include "hashtable.h"

void	ft_env()
{
	print_hashtable(g_shell->env_global);
}
