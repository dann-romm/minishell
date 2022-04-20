/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:00:45 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/20 22:00:46 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"
#include "libft_funcs.h"

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
