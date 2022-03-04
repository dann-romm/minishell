#include "shell.h"

void	ft_echo(char **args)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;

	if (!args[0])
	{
		write(1, "\n", 1);
		return ;
	}
	else if (args[0][0] == '-' && args[0][1] == 'n' && args[0][2] == '\n')
	{
		flag = 1;
		i = 1;
	}
	while (++i)
}