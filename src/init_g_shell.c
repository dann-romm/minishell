#include "shell.h"
#include "hashtable.h"

void	init_shell()
{
	g_shell = (t_shell *)malloc(sizeof(t_shell));
	g_shell->env_global = init_hashtable(10);
	g_shell->env_local = init_hashtable(10);
	fill_ht(g_shell->env_global);
}
