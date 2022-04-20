/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:01:08 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/20 22:01:09 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft_funcs.h"

// return 1 if char is a valid bash word char
// return 0 if it is a whitespace or metacharacter
static int	is_char_word(char c)
{
	return (is_alnum(c) || (!is_space(c)
			&& c > 0
			&& c != '&'
			&& c != '|'
			&& c != ';'
			&& c != '<'
			&& c != '>'
			&& c != '('
			&& c != ')'));
}

static int	tokenize_esc_char(t_source *src, char c)
{
	if (peek2(src) != c)
		return (0);
	next_char(src);
	next_char(src);
	if (c == ESCCHAR || c == '"' || c == '\'')
		save_char(src, c);
	else if (c == 'n')
		save_char(src, '\n');
	else if (c == 'r')
		save_char(src, '\r');
	else if (c == 't')
		save_char(src, '\t');
	else if (c == 'b')
		save_char(src, '\b');
	return (1);
}

static int	tokenize_double_quotes(t_source *src, t_token *token)
{
	if (peek(src) != '"')
		return (0);
	token->type = T_ID;
	next_char(src);
	while (peek(src) != EOF && peek(src) != '"')
	{
		if (peek(src) == ESCCHAR)
		{
			if (!(tokenize_esc_char(src, ESCCHAR)
					|| tokenize_esc_char(src, '"')
					|| tokenize_esc_char(src, 'n')
					|| tokenize_esc_char(src, 'r')
					|| tokenize_esc_char(src, 't')
					|| tokenize_esc_char(src, 'b')))
				save_char(src, next_char(src));
		}
		else if (!tokenize_dollar(src, token))
			save_char(src, next_char(src));
	}
	if (!(peek(src) == '"' && (next_char(src) != -42)) && peek(src) == EOF)
		token->type = T_ERROR;
	return (1);
}

static int	tokenize_quotes(t_source *src, t_token *token)
{
	if (peek(src) != '\'')
		return (0);
	token->type = T_ID;
	next_char(src);
	while (peek(src) != EOF && peek(src) != '\'')
	{
		if (peek(src) == ESCCHAR)
		{
			if (!(tokenize_esc_char(src, ESCCHAR)
					|| tokenize_esc_char(src, '\'')))
				save_char(src, next_char(src));
		}
		else
			save_char(src, next_char(src));
	}
	if (peek(src) == EOF)
		token->type = T_ERROR;
	else if (peek(src) == '\'')
		next_char(src);
	return (1);
}

int	tokenize_word(t_source *src, t_token *token)
{
	int	is_wildcard;

	if (is_char_word(peek(src)))
	{
		is_wildcard = 0;
		token->type = T_ID;
		while (is_char_word(peek(src)))
		{
			is_wildcard += (peek(src) == '*');
			if (!(tokenize_dollar(src, token)
					|| tokenize_quotes(src, token)
					|| tokenize_double_quotes(src, token)))
				save_char(src, next_char(src));
		}
		if (is_wildcard)
		{
			free(token);
			token = 0;
			handle_wildcard(src, &token);
		}
		return (1);
	}
	return (0);
}
