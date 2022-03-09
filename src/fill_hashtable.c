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
		all_paths = ft_split(env[i], '=');
		insert_hashtable(g_shell->env_global, all_paths[0], all_paths[1]);
		i++;
	}
	free(all_paths[0]);
	free(all_paths[1]);
	free(all_paths);
}
