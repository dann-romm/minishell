#include "shell.h"
#include "libft_funcs.h"

int	ft_echo(char **args, int arg_num)
{
	// printf()
	int	flag;
	int	i;

	flag = 0;
	i = -1;
	if (!args)
	{
		printf("\n");
		return (0);
	}
	else if (args[0][0] == '-' && args[0][1] == 'n' && args[0][2] == '\0')
	{
		flag = 1;
		i = 0;
	}
	while (args[++i])
	{
		printf("%s", args[i]);
		if (i < arg_num - 1)
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (0);
}
