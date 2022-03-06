#include <stdlib.h>
#include <unistd.h>
#include "libft_funcs.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*arr;
	int		len_s1;
	int		len_s2;

	if (s1 == 0 || s2 == 0)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	if (arr == 0)
		return (0);
	arr[0] = 0;
	ft_strcat(arr, s1);
	ft_strcat(arr, s2);
	return (arr);
}

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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

