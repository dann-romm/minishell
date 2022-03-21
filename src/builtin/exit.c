#include "shell.h"
#include "libft_funcs.h"

int	ft_exit(char **cmd_args, int args_num) //TODO: free all structures and arrays
{
	// free() here
	printf("exit\n");
	if (args_num == 0)
		exit(0);
	if (args_num == 1)
	{
		if (!is_numeric(cmd_args[0][0]))
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd_args[0]);
			exit(255);
		}
		else
			exit(ft_atoi(cmd_args[0]));
	}
	else
		printf("minishell: exit: too many arguments\n");
	exit(1);
}
