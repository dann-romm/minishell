/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:00:47 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/21 19:11:32 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"
#include "parser.h"
#include "libft_funcs.h"

// 1 -> token is a cmd block dilimiter
// 0 -> owervise
static int	is_token_delimiter(t_token *token)
{
	return (token != NULL && (token->type == T_ANDAND
			|| token->type == T_OROR || token->type == T_SEMI));
}

// calculate total number of cmd blocks separeted by '&&', '||' and ';'
//  N - number of cmd blocks
// -1 - syntax error
static int	count_cmd_blocks(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (is_token_delimiter(token))
			return (error_manager(ERRT_SYNTAX, token->value, -1));
		while (token && !is_token_delimiter(token))
			token = token->next;
		if (token)
		{
			if (!token->next && token->type != T_SEMI)
				return (error_manager(ERRT_SYNTAX, "newline", -1));
			token = token->next;
		}
		count++;
	}
	return (count);
}

static int	init_cmd_block(t_token **list, t_cmd_block *cmd_blocks,
	int index, t_token *delimiter)
{
	t_command_table	*table;

	table = create_command_table(list);
	if (!table)
	{
		free(cmd_blocks);
		return (1);
	}
	cmd_blocks[index].table = table;
	if (!delimiter || (delimiter->type == T_SEMI && !delimiter->next))
		cmd_blocks[index].delimiter = CMDBL_END;
	else if (delimiter->type == T_ANDAND)
		cmd_blocks[index].delimiter = CMDBL_AND;
	else if (delimiter->type == T_OROR)
		cmd_blocks[index].delimiter = CMDBL_OR;
	else if (delimiter->type == T_SEMI)
		cmd_blocks[index].delimiter = CMDBL_SEMI;
	else
	{
		errno = 1;
		delete_command_table(&table);
		free(cmd_blocks);
		return (1);
	}
	return (0);
}

static t_cmd_block	*declare_cmd_blocks(t_token **list)
{
	t_cmd_block	*cmd_blocks;
	int			count_cmdbl;

	count_cmdbl = count_cmd_blocks(*list);
	if (count_cmdbl < 0)
		errno = 258;
	if (count_cmdbl < 1)
		return (NULL);
	cmd_blocks = (t_cmd_block *)malloc(sizeof(t_cmd_block) * count_cmdbl);
	if (!cmd_blocks)
		return (NULL);
	ft_memset(cmd_blocks, 0, sizeof(t_cmd_block) * count_cmdbl);
	return (cmd_blocks);
}

t_cmd_block	*parser(t_token **list)
{
	t_cmd_block		*cmd_blocks;
	int				i;
	t_token			*tmp;
	t_token			*tmp2;

	cmd_blocks = declare_cmd_blocks(list);
	if (!cmd_blocks)
		return (NULL);
	i = -1;
	while (*list)
	{
		tmp = *list;
		while (tmp->next && !is_token_delimiter(tmp->next))
			tmp = tmp->next;
		tmp2 = tmp->next;
		tmp->next = NULL;
		if (init_cmd_block(list, cmd_blocks, ++i, tmp2))
			return (NULL);
		tmp->next = tmp2;
		list = &(tmp2);
		if (tmp2)
			list = &(tmp2->next);
	}
	return (cmd_blocks);
}
