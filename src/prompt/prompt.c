#include "shell.h"

char	*print_prompt1(void)
{
	char 	*input;

	input = readline(find_hashtable(g_shell->env_global, "PS1"));
	if (!input)
		exit(130);
	return (input);
}

char	*print_prompt2(char *input)
{
	int	i;

	i = 0;
	while (input[i])
		{
			if (ft_strcmp(&input[i], "\\") == 0)
				input = readline(find_hashtable(g_shell->env_global, "PS2"));
			i++;
		}
	return (input);
}
