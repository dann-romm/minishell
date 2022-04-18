#include "shell.h"
#include "lexer.h"
#include "parser.h"
#include "libft_funcs.h"

static int32_t	count_commands_num(t_token *list)
{
	int32_t	i;

	if (!list)
		return (0);
	i = 1;
	while (list)
	{
		i += (list->type == T_PIPE);
		list = list->next;
	}
	return (i);
}

static t_command_table	*init_command_table(t_token *list)
{
	t_command_table	*table;

	table = (t_command_table *)malloc(sizeof(t_command_table));
	if (!table)
		return (NULL);
	table->redirect._stdin = NULL;
	table->redirect._stdout = NULL;
	table->redirect.is_stdin_append = 0;
	table->redirect.is_stdout_append = 0;
	table->commands_num = count_commands_num(list);
	table->commands = (t_simple_cmd **)malloc(sizeof(t_simple_cmd *)
			* table->commands_num);
	if (!table->commands)
	{
		free(table);
		return (NULL);
	}
	ft_memset(table->commands, 0,
		sizeof(t_simple_cmd *) * table->commands_num);
	return (table);
}

static int	delete_simple_cmd(t_simple_cmd **cmd)
{
	if (!cmd || !(*cmd))
		return (1);
	if ((*cmd)->cmd)
	{
		free((*cmd)->cmd);
		(*cmd)->cmd = NULL;
	}
	while ((*cmd)->args_num--)
	{
		if ((*cmd)->cmd_args[(*cmd)->args_num])
		{
			free((*cmd)->cmd_args[(*cmd)->args_num]);
			(*cmd)->cmd_args[(*cmd)->args_num] = NULL;
		}
	}
	free((*cmd)->cmd_args);
	(*cmd)->cmd_args = NULL;
	free((*cmd));
	*cmd = NULL;
	return (0);
}

static int	delete_command_table(t_command_table **table)
{
	if (*table)
	{
		if ((*table)->redirect._stdin)
			free((*table)->redirect._stdin);
		if ((*table)->redirect._stdout)
			free((*table)->redirect._stdout);
		while ((*table)->commands_num--)
		{
			if ((*table)->commands[(*table)->commands_num])
				delete_simple_cmd(&((*table)->commands
					[(*table)->commands_num]));
		}
		free((*table)->commands);
		free((*table));
	}
	*table = NULL;
	return (0);
}

t_command_table	*create_command_table(t_token **list)
{
	t_command_table	*table;
	t_token			*tmp;
	int32_t			i;

	table = init_command_table(*list);
	if (!table)
		return (NULL);
	if (handle_redirect(table, list) || handle_parse_error(table, list))
	{
		errno = 258;
		delete_command_table(&table);
		return (NULL);
	}
	i = 0;
	tmp = *list;
	while (tmp)
	{
		table->commands[i++] = get_simple_cmd(tmp);
		while (tmp && tmp->type != T_PIPE)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (table);
}
