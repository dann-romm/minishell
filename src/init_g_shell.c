#include "shell.h"
#include "hashtable.h"

void	init_shell(char **env)
{
	g_shell = (t_shell *)malloc(sizeof(t_shell));
	g_shell->env = init_hashtable(10);
	fill_ht(env);
}
