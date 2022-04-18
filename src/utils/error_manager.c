#include "shell.h"

int	error_manager(t_error_type type, const char *msg, int error_code)
{
	printf("minishell: ");
	if (type == ERRT_SYNTAX)
		printf("syntax error near unexpected token `%s'\n", msg);
	return (error_code);
}
