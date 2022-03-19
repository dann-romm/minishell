#include "shell.h"
#include "hashtable.h"

int	ft_env()
{
	print_hashtable(g_shell->env_global);
	return (0);
}
