#include "shell.h"

// TODO: get env PS1 variable and display that
char	*read_input(char *prompt)
{
	(void)prompt;
	const char	*_DEBUG_prompt = "minishell > ";

	return (readline(_DEBUG_prompt));
}
