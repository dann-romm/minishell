#include "shell.h"

void	init_shell(char **env)
{
	int i = 0;
	char **
	while (env[i])
	{
		printf("[%d] %s\n", i, env[i]);

	// 	insert_hashtable(ht, "OLDPWD", "/Users/mgwyness/Desktop/school_21");
	// // print_hashtable(ht);
	// insert_hashtable(ht, "HOME", "/Users/mgwyness");
	// // print_hashtable(ht);
	// insert_hashtable(ht, "PWD", "/Users/mgwyness/Desktop");
	// // print_hashtable(ht);
		i++;
	}
	g_shell = (t_shell *)malloc(sizeof(t_shell));
	g_shell->env = init_hashtable(10);
}
