#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"

void	print_export_ht(t_hashtable *ht)
{
	char	**array_env;
	char	**parts_of_array;
	int		i;
	
	i = 0;
	array_env = sort_hashtable(ht);
	while (array_env[i])
	{
		parts_of_array = ft_split(array_env[i], '='); // TODO: test with a='==='
		printf("declare -x %s=\"%s\"\n", parts_of_array[0], parts_of_array[1]);
		free_2d_array(parts_of_array);
		i++;
	}
}

int	ft_export(t_simple_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd->args_num == 0)
		print_export_ht(g_shell->env_global);
	else
	{
		if (cmd->cmd_args[0][0] == '_' && cmd->cmd_args[0][1] == 0)
			return (0);
		if (check_input(cmd->cmd_args[0])) // если имя переменной состоит только из чисел или в нем есть символ типа !@#', оно невалидно
		{
			printf("minishell: export: `%s': not a valid identifier\n", cmd->cmd_args[0]);
			errno = 1;
			return (errno);
		}
		insert_hashtable(g_shell->env_global, cmd->cmd_args[0], find_hashtable(g_shell->env_local, cmd->cmd_args[0]));
	}
	return (0);
}
