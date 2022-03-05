#include "shell.h"

int	ft_exit(char **cmd_args, int args_num)
{
	printf("exit\n");
	if (args_num == 1)
		exit(0);
	else if (args_num == 2)
	{
		if (!is_isdigit(cmd_args[0]))
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
