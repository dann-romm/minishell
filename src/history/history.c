#include "shell.h"
#include "libft_funcs.h"

void	ft_add_history(char *str)
{
	char	*tmp;

	if (!str || !(*str))
		return ;
	tmp = str;
	while (*tmp)
	{
		if (!is_space(*tmp++))
		{
			add_history((const char *)str);
			return ;
		}
	}
}
