/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:00:53 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/22 20:30:05 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gshell.h"
#include "shell.h"
#include "lexer.h"
#include "libft_funcs.h"

// skip all spaces and comments in t_source
void	skip_comments(t_source *src)
{
	while (is_space(peek(src)) && peek(src) != '\n')
		next_char(src);
	if (peek(src) == '#')
	{
		while (peek(src) != '\n' && peek(src) != EOF)
			next_char(src);
	}
}

// if EOF found, initialize token with T_EOF type and return 1
// if EOL found, initialize token with T_NEWLINE type and return 1
// return 0 otherwise
int	tokenize_end_of_line(t_source *src, t_token *token)
{
	if (peek(src) == EOF || peek(src) == '\0')
	{
		token->type = T_EOF;
		save_char(src, '\0');
		next_char(src);
		return (1);
	}
	else if (peek(src) == '\n')
	{
		token->type = T_NEWLINE;
		save_char(src, next_char(src));
		return (1);
	}
	return (0);
}

// if '|' found, initialize token with T_PIPE type and return 1
// if '||' found, initialize token with T_OROR type and return 1
// return 0 otherwise
int	tokenize_pipe(t_source *src, t_token *token)
{
	if (peek(src) == '|')
	{
		token->type = T_PIPE;
		save_char(src, next_char(src));
		if (peek(src) == '|')
		{
			token->type = T_OROR;
			save_char(src, next_char(src));
		}
		return (1);
	}
	return (0);
}

// if '~' found, substitude HOME variable,
//     initialize token with T_ID type and return 1
// return 0 otherwise
int	tokenize_tilde(t_source *src, t_token *token)
{
	char	*home;

	if (peek(src) == '~' && (peek2(src) == '/'
			|| peek2(src) == EOF || is_space(peek2(src))))
	{
		token->type = T_ID;
		next_char(src);
		home = find_hashtable(g_shell.env_global, "HOME");
		while (*home)
			save_char(src, *home++);
		return (1);
	}
	return (0);
}

// initialize next token from t_source
t_token	*get_next_token(t_source *src)
{
	t_token		*token;

	token = init_token(T_ERROR, NULL);
	if (!token)
		return (NULL);
	skip_comments(src);
	if (!(tokenize_end_of_line(src, token) || tokenize_ampersand(src, token)
			|| tokenize_pipe(src, token) || tokenize_less_than(src, token)
			|| tokenize_greater_than(src, token) || tokenize_tilde(src, token)
			|| tokenize_backtick(src, token) || tokenize_semicolon(src, token)
			|| tokenize_word(src, token)))
		token->type = T_ERROR;
	token->value = ft_strdup(src->str);
	clear_str(src);
	return (token);
}
