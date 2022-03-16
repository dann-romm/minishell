#include "lexer.h"
#include "shell.h"
#include "parser.h"

int32_t	count_commands_num(t_token_list *list)
{
	int32_t	i;

	if (!list)
		return (0);
	i = 1;
	while (list)
	{
		i += (list->token->type == T_PIPE);
		list = list->next;
	}
	return (i);
}

int32_t	count_cmd_args(t_token_list *list)
{
	int32_t	i;

	i = 0;
	while (list && list->token->type != T_PIPE)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_simple_cmd	*init_simple_cmd(t_token_list *list)
{
	t_simple_cmd	*cmd;
	int32_t			i;

	if (!list)
		return (NULL);
	cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!cmd)
		return (NULL);
	cmd->args_num = count_cmd_args(list) - 1;
	if (cmd->args_num)
		cmd->cmd_args = (char **)malloc(sizeof(char *) * cmd->args_num);
	else
		cmd->cmd_args = NULL;
	cmd->cmd = list->token->value;
	list = list->next;
	i = 0;
	while (list && list->token->type != T_PIPE)
	{
		cmd->cmd_args[i++] = list->token->value;
		list = list->next;
	}
	return (cmd);
}

t_command_table	*init_command_table(void)
{
	t_command_table	*table;

	table = (t_command_table *)malloc(sizeof(t_command_table));
	if (!table)
	{
		errno = ENOMEM;
		return (NULL);
	}
	table->redirect._stdin = NULL;
	table->redirect._stdout = NULL;
	return (table);
}

int	handle_assignments(t_token_list *list)
{
	t_token_list	*tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (tmp->next->token->type == T_EQUALS)
		{
			if (!tmp->next->next || tmp->token->type != T_ID)
				return (1);
		}
		tmp = tmp->next;
	}
	
}

t_command_table	*parser(t_token_list *list)
{
	t_command_table	*table;
	int32_t			i;

	table = init_command_table();
	// handle_assignments(list); // TODO





	table->commands_num = count_commands_num(list);
	table->commands = (t_simple_cmd **)malloc(sizeof(t_simple_cmd *) * table->commands_num);
	if (!table->commands)
	{
		free(table);
		return (NULL);
	}
	printf("count = %d\n", table->commands_num);
	i = 0;
	while (list)
	{
		table->commands[i++] = init_simple_cmd(list);
		while (list && list->token->type != T_PIPE)
			list = list->next;
		if (list)
			list = list->next;
	}

	return (table);
}
