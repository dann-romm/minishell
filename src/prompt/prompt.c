#include "shell.h"

// TODO: get env PS1 variable and display that
char	*read_input(char *prompt)
{
	(void)prompt;
	const char	*input = "minishell > ";

	return (readline(input));
}
