#include "shell.h"

void	init_ht(t_hashtable *ht, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("[%d] %s\n", env[i]);
		insert_hashtable(ht, "OLDPWD", "/Users/mgwyness/Desktop/school_21");
	// print_hashtable(ht);
	insert_hashtable(ht, "HOME", "/Users/mgwyness");
	// print_hashtable(ht);
	insert_hashtable(ht, "PWD", "/Users/mgwyness/Desktop");
	// print_hashtable(ht);
	}
}