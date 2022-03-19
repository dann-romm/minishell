#include "lexer.h"
#include "shell.h"
#include "parser.h"
#include "libft_funcs.h"

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
	{
		command->cmd_args = (char **)malloc(sizeof(char *) * (command->args_num + 1));
		command->cmd_args[command->args_num] = NULL;
	}
	else
		command->cmd_args = NULL;
	return (command);
}

int	delete_simple_cmd(t_simple_cmd **cmd)
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

// 0 - no assignment found
// 1 - assignment handled successful
int	handle_assignment(t_simple_cmd **command, t_token_list *list)
{
	if (list->next && list->next->token->type == T_EQUALS)
		*command = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	else
		return (0);
	if (!(*command))
		return (1);
	(*command)->args_num = 2;
	(*command)->cmd = NULL;
	(*command)->type = CMD_ASSIGNMENT;
	(*command)->cmd_args = (char **)malloc(sizeof(char *) * 2);
	if (!(*command)->cmd_args)
	{
		free(*command);
		*command = NULL;
		return (1);
	}
	(*command)->cmd_args[0] = ft_strdup(list->token->value);
	(*command)->cmd_args[1] = ft_strdup(list->next->next->token->value);
	return (1);
}

int	define_cmd_type(t_simple_cmd *command)
{
	if (!command)
		return (1);
	if (!command->cmd)
	{
		command->type = CMD_NONE;
		return (0);
	}
	if (!ft_strcmp(command->cmd, "cd"))
		command->type = CMD_CD;
	else if (!ft_strcmp(command->cmd, "echo"))
		command->type = CMD_ECHO;
	else if (!ft_strcmp(command->cmd, "env"))
		command->type = CMD_ENV;
	else if (!ft_strcmp(command->cmd, "exit"))
		command->type = CMD_EXIT;
	else if (!ft_strcmp(command->cmd, "export"))
		command->type = CMD_EXPORT;
	else if (!ft_strcmp(command->cmd, "pwd"))
		command->type = CMD_PWD;
	else if (!ft_strcmp(command->cmd, "unset"))
		command->type = CMD_UNSET;
	else
		command->type = CMD_NONE;
	return (0);
}

t_simple_cmd	*get_simple_cmd(t_token_list *list)
{
	t_simple_cmd	*command;
	int32_t			i;

	if (handle_assignment(&command, list))
		return (command);
	command = init_simple_cmd(list);
	command->cmd = ft_strdup(list->token->value);
	list = list->next;
	i = 0;
	while (list && list->token->type != T_PIPE)
	{
		command->cmd_args[i++] = ft_strdup(list->token->value);
		list = list->next;
	}
	define_cmd_type(command);
	return (command);
}
