#include "lexer.h"
#include "shell.h"
#include "parser.h"
#include "libft_funcs.h"

#include "debug.h" // to remove

int32_t	count_commands_num(t_token *list)
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

t_command_table	*init_command_table(t_token *list)
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
	table->commands = (t_simple_cmd **)malloc(sizeof(t_simple_cmd *) * table->commands_num);
	if (!table->commands)
	{
		free(table);
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

int	handle_redirect(t_command_table *table, t_token **list)
{
	t_token	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->type == T_GREAT || tmp->type == T_DGREAT
			|| tmp->type == T_LESS || tmp->type == T_DLESS)
		{
			if (!tmp->next || tmp->next->type != T_ID)
				return (1); // syntax error
			if (tmp->type == T_GREAT || tmp->type == T_DGREAT)
				table->redirect._stdout = ft_strdup(tmp->next->value);
			if (tmp->type == T_LESS || tmp->type == T_DLESS)
				table->redirect._stdin = ft_strdup(tmp->next->value);
			if (tmp->type == T_DGREAT)
				table->redirect.is_stdout_append = 1;
			else if (tmp->type == T_DLESS)
				table->redirect.is_stdin_append = 1;
			remove_token_list(list, &tmp);
			remove_token_list(list, &tmp);
		}
		else
			tmp = tmp->next;
	}
	return (0);
}

int	handle_parse_error(t_command_table *table, t_token **list)
{
	t_token	*tmp;
	int32_t	is_cmd;

	is_cmd = 0;
	tmp = *list;
	while (tmp)
	{
		if (tmp->type == T_EQUALS && (is_cmd == 0 || !tmp->next || tmp->next->type != T_ID || (tmp->next->next != 0 && tmp->next->next->type != T_PIPE)))
			return (1);
		if (tmp->type == T_PIPE && is_cmd == 0)
			return (1);
		if (tmp->type == T_ID)
			is_cmd++;
		if (tmp->type == T_PIPE)
			is_cmd = 0;
		tmp = tmp->next;
	}
	return (!is_cmd);
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
		return (NULL); // display syntax error message
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

int	is_token_delimiter(t_token *token)
{
	return (token != NULL && (token->type == T_ANDAND || token->type == T_OROR || token->type == T_SEMI));
}

// -1 - on error
// N - number of total cmd blocks separated with (&& || ;)
int	count_cmd_blocks(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (is_token_delimiter(token))
		{
			printf("minishell: syntax error near unexpected token `%s'\n", token->value);
			errno = 258;
			return (-1);
		}
		while (token && !is_token_delimiter(token))
			token = token->next;
		if (token)
		{
			token = token->next;
			if (!token) // TODO: there's no error when ';' at the end
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				errno = 258;
				return (-1);
			}
		}
		count++;
	}
	return (count);
}

int	init_cmd_block(t_token **list, t_cmd_block *cmd_blocks, int index)
{
	t_command_table	*table;

	table = create_command_table(list);
	cmd_blocks[++index].table = table;
	cmd_blocks[++index].delimiter = CMDBL_AND; // fix delimiter initialization
	_DEBUG_print_command_table(table);
	delete_command_table(&table);
	return (0);
}

t_cmd_block	*parser(t_token **list)
{
	t_cmd_block		*cmd_blocks;
	int				count_cmdbl;
	int				i;

	t_token			*tmp;
	t_token			*tmp2;

	count_cmdbl = count_cmd_blocks(*list);
	printf("count_cmd_blocks = %d\n", count_cmdbl);
	if (count_cmdbl < 1)
		return (NULL);

	cmd_blocks = (t_cmd_block *)malloc(sizeof(t_cmd_block) * count_cmdbl);
	i = -1;

	while (*list)
	{
		tmp = *list;
		while (tmp->next && !is_token_delimiter(tmp->next))
			tmp = tmp->next;
		tmp2 = tmp->next;
		tmp->next = NULL;

		init_cmd_block(list, cmd_blocks, i);
		
		tmp->next = tmp2;
		list = &(tmp2);
		if (tmp2)
			list = &(tmp2->next);
	}
	// _DEBUG_print_token(*list);
	// _DEBUG_print_token(tmp);
	// _DEBUG_print_token(tmp2);
	return (NULL); // remove
}

// ls | cat && ls2 | cat2