#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"

// if env looks like this
// KEY: 'a'
// VALUE: 'b==b=b=b=b=b=b==bb'
// ft_split vill split that into 10+ strings, so you will put only first 'b' into hastable
// also you have mem leak at all_paths[2], all_paths[3], so one and so forth
void	fill_hashtable(char **env)
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
