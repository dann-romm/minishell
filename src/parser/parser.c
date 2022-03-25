#include "lexer.h"
#include "shell.h"
#include "parser.h"
#include "libft_funcs.h"

#include "debug.h" // to remove

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

t_command_table	*init_command_table(t_token_list *list)
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
	table->redirect.is_stdin_append = 0;
	table->redirect.is_stdout_append = 0;
	table->commands_num = count_commands_num(list);
	table->commands = (t_simple_cmd **)malloc(sizeof(t_simple_cmd *) * table->commands_num);
	if (!table->commands)
	{
		free(table);
		errno = ENOMEM;
		return (NULL);
	}
	for (int i = 0; i < table->commands_num; i++) // replace with memset
		table->commands[i] = NULL; // replace with memset
	return (table);
}

int	delete_command_table(t_command_table **table)
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
				delete_simple_cmd(&((*table)->commands[(*table)->commands_num]));
		}
		free((*table)->commands);
		free((*table));
	}
	*table = NULL;
	return (0);
}

int	handle_redirect(t_command_table *table, t_token_list **list)
{
	t_token_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->token->type == T_GREAT || tmp->token->type == T_DGREAT
			|| tmp->token->type == T_LESS || tmp->token->type == T_DLESS)
		{
			if (!tmp->next || tmp->next->token->type != T_ID)
				return (1); // syntax error
			if (tmp->token->type == T_GREAT || tmp->token->type == T_DGREAT)
				table->redirect._stdout = ft_strdup(tmp->next->token->value);
			if (tmp->token->type == T_LESS || tmp->token->type == T_DLESS)
				table->redirect._stdin = ft_strdup(tmp->next->token->value);
			if (tmp->token->type == T_DGREAT)
				table->redirect.is_stdout_append = 1;
			else if (tmp->token->type == T_DLESS)
				table->redirect.is_stdin_append = 1;
			remove_token_list(list, &tmp);
			remove_token_list(list, &tmp);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

int	handle_parse_error(t_command_table *table, t_token_list **list)
{
	t_token_list	*tmp;
	int32_t			is_cmd;

	is_cmd = 0;
	tmp = *list;
	while (tmp)
	{
		if (tmp->token->type == T_EQUALS && (is_cmd == 0 || !tmp->next || tmp->next->token->type != T_ID || (tmp->next->next != 0 && tmp->next->next->token->type != T_PIPE)))
			return (1);
		if (tmp->token->type == T_PIPE && is_cmd == 0)
			return (1);
		if (tmp->token->type == T_ID)
			is_cmd++;
		if (tmp->token->type == T_PIPE)
			is_cmd = 0;
		tmp = tmp->next;
	}
	return (!is_cmd);
}

t_command_table	*parser(t_token_list **list)
{
	t_command_table	*table;
	t_token_list	*tmp;
	int32_t			i;

	table = init_command_table(*list);
	if (!table)
		return (0);
	
	if (handle_redirect(table, list) || handle_parse_error(table, list))
		return (0); // syntax error

	i = 0;
	tmp = *list;
	while (tmp)
	{
		table->commands[i++] = get_simple_cmd(tmp);
		while (tmp && tmp->token->type != T_PIPE)
			tmp = tmp->next;
		if (tmp)
			tmp = tmp->next;
	}
	return (table);
}
