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
	return (table);
}

int	handle_redirect(t_command_table *table, t_token_list **list) // segfault at command > text.txt
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
			remove_token_list(&tmp);
			remove_token_list(&tmp);
			if (tmp && tmp->token->type != T_PIPE)
				return (1); // syntax error
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

t_command_table	*parser(t_token_list *list)
{
	t_command_table	*table;
	int32_t			i;

	table = init_command_table(list);
	if (!table)
		return (0);
	
	if (handle_redirect(table, &list))
		return (0); // syntax error

	i = 0;
	while (list)
	{
		table->commands[i++] = get_simple_cmd(list);
		while (list && list->token->type != T_PIPE)
			list = list->next;
		if (list)
			list = list->next;
	}

	return (table);
}
