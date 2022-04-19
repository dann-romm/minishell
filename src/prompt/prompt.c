#include "shell.h"
#include "libft_funcs.h"

char	*prompt1(void) // TODO: fix the output
{
	char 	*input;

	input = readline(find_hashtable(g_shell->env_local, "PS1"));
	if (!input)
	{
		// write(2, "exit\n", 5);
		rl_redisplay();
		exit(130);
	}
	return (input);
}

char	*prompt2(void)
{
	return (readline(find_hashtable(g_shell->env_local, "PS2")));
}
