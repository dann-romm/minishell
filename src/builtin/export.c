#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"

int	check_input(char *str) 
{
	int	i;
	int	count1;
	int	count2;

	i = -1;
	count1 = 0;
	count2 = 0;
	while (str[++i])
	{
		if ((!ft_isdigit(str[i]) && !ft_isalpha(str[i])) || ft_isdigit(str[0]))
			return (1);
		else if (ft_isdigit(str[i]))
			count1++;
	}
	if (count1 == i - 1)
		return (1);
	return (0);
}

void	ft_export(t_hashtable *ht, char **args)
{
	if (check_input(args[0])) // если имя переменной состоит только из чисел или в нем есть символ типа !@#', оно невалидно
	{
		printf("minishell: export: `%s': not a valid identifier", args[1]);
		return ;
	}
	insert_hashtable(ht, args[0], args[1]);
}
