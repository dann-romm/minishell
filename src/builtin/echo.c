#include "shell.h"
#include "libft_funcs.h"

void	ft_echo(char **args, int arg_num)
{
	int	flag;
	int	i;

	flag = 0;
	i = -1;
	if (!args)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (args[0][0] == '-' && args[0][1] == 'n' && args[0][2] == '\0')
	{
		flag = 1;
		i = 0;
	}
	while (args[++i])
	{
		ft_putstr(args[i]);
		if (i < arg_num - 1)
			write(1, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
}
