#include "shell.h"
#include "libft_funcs.h"

char	*prompt1(void) //fix the output
{
	char 	*input;

	input = readline(find_hashtable(g_shell->env_global, "PS1"));
	if (!input)
	{
		rl_redisplay();
		// printf("exit\n");
		// write(0, "exit\n", 5);
		exit(130);
	}
	return (input);
}

char	*prompt2(void)
{
	return (readline(find_hashtable(g_shell->env_global, "PS2")));
}
