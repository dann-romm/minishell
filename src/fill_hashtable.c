#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"

void	fill_ht(char **env)
{
	int		i;
	char	**all_paths;

	i = 0;
	while (env[i])
	{
		// printf("[%d] %s\n", i, env[i]);
		all_paths = ft_split(env[i], '=');
		insert_hashtable(g_shell->env, all_paths[0], all_paths[1]);
		// printf("%d -> %s %s\n", i, all_paths[0], all_paths[1]);
	// 	insert_hashtable(ht, "OLDPWD", "/Users/mgwyness/Desktop/school_21");
	// // print_hashtable(ht);
	// insert_hashtable(ht, "HOME", "/Users/mgwyness");
	// // print_hashtable(ht);
	// insert_hashtable(ht, "PWD", "/Users/mgwyness/Desktop");
	// // print_hashtable(ht);
		i++;
	}
}