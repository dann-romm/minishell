/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:00:45 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/21 16:40:59 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "parser.h"
#include "lexer.h"
#include "libft_funcs.h"

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
				delete_simple_cmd(&((*table)->commands
					[(*table)->commands_num]));
		}
		free((*table)->commands);
		free((*table));
	}
	*table = NULL;
	return (0);
}

int	delete_cmd_blocks(t_cmd_block **cmd_blocks)
{
	int	i;

	if (!cmd_blocks || !(*cmd_blocks))
		return (1);
	i = 0;
	while ((*cmd_blocks)[i].delimiter != CMDBL_END)
	{
		delete_command_table(&((*cmd_blocks)[i].table));
		i++;
	}
	delete_command_table(&((*cmd_blocks)[i].table));
	free(*cmd_blocks);
	*cmd_blocks = NULL;
	return (0);
}

// if there is a redirect, fills t_command_table fields
// 0 -> success handling
// 1 -> syntax error
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
				return (error_manager(ERRT_SYNTAX, tmp->value, 1));
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

// checks syntax near '=' and '|' tokens
// 0 -> success handling
// 1 -> syntax error
int	handle_parse_error(t_command_table *table, t_token **list)
{
	t_token	*tmp;
	int32_t	is_cmd;

	(void) table;
	is_cmd = 0;
	tmp = *list;
	while (tmp)
	{
		if (is_cmd == 0 && tmp->type == T_PIPE)
			return (error_manager(ERRT_SYNTAX, tmp->value, 1));
		else if (tmp->type == T_ID)
			is_cmd = 1;
		else if (tmp->type == T_PIPE)
			is_cmd = 0;
		tmp = tmp->next;
	}
	if (!is_cmd)
		error_manager(ERRT_SYNTAX, "newline", 1);
	return (!is_cmd);
}
