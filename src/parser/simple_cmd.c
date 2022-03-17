#include "lexer.h"
#include "shell.h"
#include "parser.h"

// TODO: < text.txt segfault

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
	t_simple_cmd	*command;

	if (!list)
		return (NULL);
	command = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!command)
		return (NULL);
	command->args_num = count_cmd_args(list) - 1;
	if (command->args_num)
		command->cmd_args = (char **)malloc(sizeof(char *) * command->args_num);
	else
		command->cmd_args = NULL;
	return (command);
}

t_simple_cmd	*get_simple_cmd(t_token_list *list)
{
	t_simple_cmd	*command;
	int32_t			i;

	command = init_simple_cmd(list);


	command->cmd = list->token->value;
	list = list->next;
	i = 0;
	while (list && list->token->type != T_PIPE)
	{
		command->cmd_args[i++] = list->token->value;
		list = list->next;
	}
	return (command);
}
