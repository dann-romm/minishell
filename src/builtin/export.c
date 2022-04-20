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

// TODO:

// пример параметра t_simple_cmd:
// type = CMD_EXPORT
// cmd = "export"
// args_num = 4
// args[4] = [ "a=value" ('a', 'value'), "b===value" ('b', '==value'), "123rr=value==" ('123rr', 'value=='), "-123=value" ('-123', 'value') ]

// перенести (если есть) все переменные args из local_env (если они там есть) в global_env
// на каждую невалидную переменную вывести ошибку



int	ft_export(t_simple_cmd *cmd)
{
	int		i;
	char	*name;
	char	*value;
	char	*eq;
	int		j;

	if (cmd->args_num == 0)
	{
		print_export_ht(g_shell->env_global);
		return (errno);
	}


	i = -1;
	while (++i < cmd->args_num)
	{
		if (cmd->cmd_args[i][0] == '_' && cmd->cmd_args[i][1] == 0)
			continue ;

		//j = 0;
		//while (cmd->cmd_args[i][j] != '=')
		//	j++;
		//name = ft_strndup(cmd->cmd_args[i], j);
		//value = ft_strchr(cmd->cmd_args[i], '=');

		eq = ft_strchr(cmd->cmd_args[i], '=');
		if (eq)
		{

		}
		else
		{
			
		}

		if (check_input(name))
		{
			printf("minishell: export: `%s': not a valid identifier\n", cmd->cmd_args[i]);
			errno = 1;
		}
		else
			insert_hashtable(g_shell->env_global, name, value); // this value must be replaced with local_env value
		//printf("name = %s value = %s\n", name, value);
		//print_hashtable(g_shell->env_local);
		free(name);
	}

	return (errno);
}
