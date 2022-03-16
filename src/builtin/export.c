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
		if (str[0] != '_' && ((!is_numeric(str[i]) && !is_alpha(str[i])) || is_numeric(str[0])))
			return (1);
		else if (is_numeric(str[i]))
			count1++;
	}
	if (count1 == i - 1)
		return (1);
	return (0);
}

void	print_export_ht(t_hashtable *ht)
{
	t_pair	*pair;
	int		i;

	i = -1;
	while (++i < ht->size)
	{
		pair = ht->table[i];
		while (pair)
		{
			printf("declare -x %s=""%s""\n", pair->key, pair->value);
			pair = pair->next;
		}
	}
}


void	ft_export(t_simple_cmd *cmd)
{
	int	i;
	char *res;

	i = 0;
	if (cmd->args_num == 0)
		print_export_ht(g_shell->env_global);
	if (cmd->cmd_args[0][1] == 0 && cmd->cmd_args[0][0] == '_')
		return ;
	if (check_input(cmd->cmd_args[0])) // если имя переменной состоит только из чисел или в нем есть символ типа !@#', оно невалидно
	{
		printf("minishell: export: `%s': not a valid identifier\n", cmd->cmd_args[0]);
		return ;
	}
	insert_hashtable(g_shell->env_global, cmd->cmd_args[0], find_hashtable(g_shell->env_local, cmd->cmd_args[0]));
	free(res);
}
