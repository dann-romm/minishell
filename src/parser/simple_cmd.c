#include "lexer.h"
#include "shell.h"
#include "parser.h"
#include "libft_funcs.h"

// calculate argument number before pipe
// e.g. <echo> <1> <|> <ls> -> 2 (echo and 1)
// e.g. <make> <re> -> 2 (make and re)
int32_t	count_cmd_args(t_token *list)
{
	int32_t	i;

	i = 0;
	while (list && list->type != T_PIPE)
	{
		i++;
		list = list->next;
	}
	return (i);
}

// calculate space for t_simple_cmd struct and initialize it
t_simple_cmd	*init_simple_cmd(t_token *list)
{
	t_simple_cmd	*cmd;

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
	return (cmd);
}

// 0 - no assignment found
// 1 - assignment handled successfully
// if there is an assignment, initialize cmd
int	handle_assignment(t_simple_cmd **cmd, t_token *list)
{
	int	i;

	*cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	if (!(*cmd))
		return (1);
	(*cmd)->args_num = count_cmd_args(list);
	(*cmd)->cmd = NULL;
	(*cmd)->type = CMD_ASSIGNMENT;
	(*cmd)->cmd_args = (char **)malloc(sizeof(char *) * (*cmd)->args_num);
	if (!(*cmd)->cmd_args)
	{
		free(*cmd);
		*cmd = NULL;
		return (1);
	}
	ft_memset((*cmd)->cmd_args, 0, sizeof(char *) * (*cmd)->args_num);
	i = 0;
	while (list)
	{
		if (!ft_strchr(list->value, '=') && !delete_simple_cmd(cmd))
			return (1);
		(*cmd)->cmd_args[i++] = ft_strdup(list->value);
		list = list->next;
	}
	return (1);
}

// defines t_simple_cmd type according to it's command name
// e.g. if command->cmd == "pwd" then cmd_type == CMD_PWD
int	define_cmd_type(t_simple_cmd *cmd)
{
	if (!cmd)
		return (1);
	if (!cmd->cmd)
	{
		cmd->type = CMD_NONE;
		return (0);
	}
	if (!ft_strcmp(cmd->cmd, "cd"))
		cmd->type = CMD_CD;
	else if (!ft_strcmp(cmd->cmd, "echo"))
		cmd->type = CMD_ECHO;
	else if (!ft_strcmp(cmd->cmd, "env"))
		cmd->type = CMD_ENV;
	else if (!ft_strcmp(cmd->cmd, "exit"))
		cmd->type = CMD_EXIT;
	else if (!ft_strcmp(cmd->cmd, "export"))
		cmd->type = CMD_EXPORT;
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		cmd->type = CMD_PWD;
	else if (!ft_strcmp(cmd->cmd, "unset"))
		cmd->type = CMD_UNSET;
	else
		cmd->type = CMD_NONE;
	return (0);
}

// create t_simple_cmd from token list
t_simple_cmd	*get_simple_cmd(t_token *list)
{
	t_simple_cmd	*cmd;
	int32_t			i;

	if (handle_assignment(&cmd, list))
		return (cmd);
	cmd = init_simple_cmd(list);
	cmd->cmd = ft_strdup(list->value);
	list = list->next;
	i = 0;
	while (list && list->type != T_PIPE)
	{
		cmd->cmd_args[i++] = ft_strdup(list->value);
		list = list->next;
	}
	define_cmd_type(cmd);
	return (cmd);
}
