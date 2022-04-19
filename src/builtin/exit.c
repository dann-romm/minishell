#include "shell.h"
#include "libft_funcs.h"

int	ft_exit(char **cmd_args, int args_num) //TODO: free all structures and arrays
{
	// free() here
	printf("exit\n");
	if (args_num == 0)
		exit(errno);
	else if (args_num == 1)
	{
		if (!is_str_numeric(cmd_args[0]))
		{
			printf("minishell: exit: %s: Numeric argument required\n", cmd_args[0]);
			errno = 255;
			exit(errno);
		}
		else
			exit(ft_atoi(cmd_args[0]));
	}
	else
	{
		printf("minishell: exit: Too many arguments\n");
		errno = 1;
	}
	return (0);
}
