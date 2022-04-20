/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:01:06 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/20 22:01:07 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"

// if '&' found, initialize token with T_AND type and return 1
// if '&&' found, initialize token with T_ANDAND type and return 1
// return 0 otherwise
int	tokenize_ampersand(t_source *src, t_token *token)
{
	if (peek(src) == '&')
	{
		token->type = T_AND;
		save_char(src, next_char(src));
		if (peek(src) == '&')
		{
			token->type = T_ANDAND;
			save_char(src, next_char(src));
		}
		return (1);
	}
	return (0);
}

// if '<' found, initialize token with T_LESS type and return 1
// if '<&' found, initialize token with T_LESSAND type and return 1
// if '<>' found, initialize token with T_LESSGREAT type and return 1
// if '<<' found, initialize token with T_DLESS type and return 1
// if '<<-' found, initialize token with T_DLESSDASH type and return 1
// return 0 otherwise
int	tokenize_less_than(t_source *src, t_token *token)
{
	if (peek(src) != '<')
		return (0);
	token->type = T_LESS;
	save_char(src, next_char(src));
	if (peek(src) == '&')
	{
		token->type = T_LESSAND;
		save_char(src, next_char(src));
	}
	else if (peek(src) == '>')
	{
		token->type = T_LESSGREAT;
		save_char(src, next_char(src));
	}
	else if (peek(src) == '<')
	{
		token->type = T_DLESS;
		save_char(src, next_char(src));
		if (peek(src) == '-')
		{
			token->type = T_DLESSDASH;
			save_char(src, next_char(src));
		}
	}
	return (1);
}

// if '>' found, initialize token with T_GREAT type and return 1
// if '>&' found, initialize token with T_GREATAND type and return 1
// if '>>' found, initialize token with T_DGREAT type and return 1
// if '>|' found, initialize token with T_CLOBBER type and return 1
// return 0 otherwise
int	tokenize_greater_than(t_source *src, t_token *token)
{
	if (peek(src) == '>')
	{
		token->type = T_GREAT;
		save_char(src, next_char(src));
		if (peek(src) == '&')
		{
			token->type = T_GREATAND;
			save_char(src, next_char(src));
		}
		else if (peek(src) == '>')
		{
			token->type = T_DGREAT;
			save_char(src, next_char(src));
		}
		else if (peek(src) == '|')
		{
			token->type = T_CLOBBER;
			save_char(src, next_char(src));
		}
		return (1);
	}
	return (0);
}

// int	tokenize_equals(t_source *src, t_token *token)
// {
// 	if (peek(src) == '=')
// 	{
// 		token->type = T_EQUALS;
// 		save_char(src, next_char(src));
// 		return (1);
// 	}
// 	return (0);
// }

int	tokenize_semicolon(t_source *src, t_token *token)
{
	if (peek(src) == ';')
	{
		token->type = T_SEMI;
		save_char(src, next_char(src));
		if (peek(src) == ';')
		{
			token->type = T_DSEMI;
			save_char(src, next_char(src));
		}
		return (1);
	}
	return (0);
}

int	tokenize_backtick(t_source *src, t_token *token)
{
	if (peek(src) == '`')
	{
		token->type = T_BACKTICK;
		next_char(src);
		while (peek(src) != EOF && peek(src) != '`')
			save_char(src, next_char(src));
		if (peek(src) == EOF)
			token->type = T_ERROR;
		else
			next_char(src);
		return (1);
	}
	return (0);
}
