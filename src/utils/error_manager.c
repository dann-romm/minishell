#include "shell.h"

int	error_manager(t_error_type type, const char *msg, int error_code)
{
	printf("minishell: ");
	if (type == ERRT_SYNTAX)
		printf("syntax error near unexpected token `%s'\n", msg);
	else if (type == ERRT_PWD_ERR)
		printf("%s: %s\n", find_hashtable(g_shell->env_global, "PWD"),
			strerror(errno));
	else if (type == ERRT_UNSUPPORTED)
		printf("`%s': is not supported in this version of minishell\n", msg);
	return (error_code);
}
