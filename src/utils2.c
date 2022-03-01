#include "shell.h"

void	ft_putstr(char *s)
{
	int	i;

	if (s == 0)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_putendl(char *s)
{
	if (s == 0)
		return ;
	ft_putstr(s);
	write(1, "\n", 1);
}
