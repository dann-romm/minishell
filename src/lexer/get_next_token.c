#include "lexer.h"
#include "libft_funcs.h"
#include "shell.h"

// skip all spaces and comments
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
// return 0 otherwise
int	tokenize_end_of_file(t_source *src, t_token *token)
{
	if (peek(src) == EOF || peek(src) == '\0')
	{
		token->type = T_EOF;
		save_char(src, '\0');
		next_char(src);
		return (1);
	}
	return (0);
}

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

int	tokenize_newline(t_source *src, t_token *token)
{
	if (peek(src) == '\n')
	{
		token->type = T_NEWLINE;
		save_char(src, next_char(src));
		return (1);
	}
	return (0);
}

int	tokenize_tilde(t_source *src, t_token *token)
{
	char	*home;

	if (peek(src) == '~' && (peek2(src) == '/'
		|| peek2(src) == EOF || is_space(peek2(src))))
	{
		token->type = T_ID;
		next_char(src);
		home = find_hashtable(g_shell->env_global, "HOME");
		while (*home)
			save_char(src, *home++);
		return (1);
	}
	return (0);
}

t_token	*get_next_token(t_source *src)
{
	t_token		*token;

	token = init_token(T_ERROR, NULL);
	if (!token)
		return (NULL);
	skip_comments(src);
	if (!(tokenize_end_of_file(src, token) || tokenize_ampersand(src, token)
		|| tokenize_pipe(src, token) || tokenize_less_than(src, token)
		|| tokenize_greater_than(src, token) || tokenize_semicolon(src, token)
		|| tokenize_backtick(src, token) || tokenize_tilde(src, token)
		|| tokenize_newline(src, token) || tokenize_word(src, token)))
		token->type = T_ERROR;
	token->value = ft_strdup(src->str);
	clear_str(src);
	return (token);
}
