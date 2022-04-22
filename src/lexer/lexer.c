/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:00:55 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/22 21:15:20 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"

static int	is_valid_token(t_token *token)
{
	if (token->type == T_ERROR)
		return (0);
	if (token->type == T_IF || token->type == T_THEN
		|| token->type == T_ELSE || token->type == T_FOR || token->type == T_FI
		|| token->type == T_ELIF || token->type == T_IN || token->type == T_DO
		|| token->type == T_BREAK || token->type == T_CONTINUE
		|| token->type == T_WHILE || token->type == T_DONE
		|| token->type == T_LESSAND || token->type == T_GREATAND
		|| token->type == T_LESSGREAT || token->type == T_DLESSDASH
		|| token->type == T_CLOBBER || token->type == T_DSEMI
		|| token->type == T_BACKTICK)
		return (error_manager(ERRT_UNSUPPORTED, token->value, 0));
	return (1);
}

t_token	*lexer(char *input)
{
	t_source	*src;
	t_token		*token;
	t_token		*head;

	head = NULL;
	src = init_source(input);
	if (!src)
		return (0);
	token = get_next_token(src);
	while (token && token->type != T_EOF)
	{
		if (!is_valid_token(token))
		{
			errno = error_manager(ERRT_SYNTAX, token->value, 258);
			delete_token(&token);
			break ;
		}
		push_back_token_list(&head, token);
		token = get_next_token(src);
	}
	if (!token)
		delete_token_list(&head);
	delete_token(&token);
	delete_source(&src);
	return (head);
}
