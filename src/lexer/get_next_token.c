#include "lexer.h"
#include "libft_funcs.h"
#include "shell.h"

void	skip_comments(t_source *src)
{
	while (is_space(peek(src)) && peek(src) != '\n')
		next_char(src);
	if (peek(src) == '#')
	{
		while (peek(src) != '\n')
			next_char(src);
	}
}

// * ? [ ]
// ( )
// $ & | ; < >
int	is_char_word(char c)
{
	return (is_alnum(c) || ( !is_space(c)
		&& c > 0
		&& c != '&'
		&& c != '|'
		&& c != ';'
		&& c != '<'
		&& c != '>'
		&& c != '('
		&& c != ')'));
}

void	put_exit_status_into_src(t_source *src)
{
	const char	*exit_status = ft_itoa(g_shell->exit_status);
	int			i;

	if (!exit_status)
		return ;
	i = 0;
	while (exit_status[i])
		save_char(src, exit_status[i++]);
}

void	put_env_into_src(t_source *src)
{
	t_source	*tmp;
	char		*key;
	char		*value;

	tmp = init_source("");
	while (is_alnum(peek(src)) || peek(src) == '_')
		save_char(tmp, next_char(src));
	key = ft_strdup(tmp->str);
	value = find_hashtable(g_shell->env_global, key);
	clear_str(tmp);
	while (value && *value)
		save_char(src, *value++);
	free(key);
	delete_source(&tmp);
}

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

int	tokenize_less_than(t_source *src, t_token *token)
{
	if (peek(src) == '<')
	{
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
	return (0);
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

int	tokenize_equals(t_source *src, t_token *token)
{
	if (peek(src) == '=')
	{
		token->type = T_EQUALS;
		save_char(src, next_char(src));
		return (1);
	}
	return (0);
}

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
		next_char(src);
		while (peek(src) != EOF && peek(src) != '`')
			save_char(src, next_char(src));
		token->type = T_BACKTICK;
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

int	tokenize_dollar(t_source *src, t_token *token)
{
	int	require_bracket;

	if (peek(src) == '$')
	{
		require_bracket = 0;
		next_char(src);
		if (peek(src) == '?')
		{
			next_char(src);
			put_exit_status_into_src(src);
			token->type = T_ID;
		}
		else // TODO: special parameter https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_02
		{
			if (peek(src) == '{')
			{
				require_bracket = 1;
				next_char(src);
			}
			put_env_into_src(src);
			if (require_bracket && peek(src) != '}')
				token->type = T_ERROR;
			else if (require_bracket)
				next_char(src);
			token->type = T_ID;
		}
		return (1);
	}
	return (0);
}

int	tokenize_double_quotes(t_source *src, t_token *token)
{
	if (peek(src) == '"')
	{
		token->type = T_ID;
		next_char(src);
		while (peek(src) != EOF && peek(src) != '"')
		{
			if (peek(src) == ESCCHAR)
			{
				if (peek2(src) == ESCCHAR)
				{
					next_char(src);
					save_char(src, next_char(src));
				}
				else if (peek2(src) == '"')
				{
					next_char(src);
					save_char(src, next_char(src));
				}
				else if (peek2(src) == 'n')
				{
					next_char(src);
					next_char(src);
					save_char(src, '\n');
				}
				else if (peek2(src) == 'r')
				{
					next_char(src);
					next_char(src);
					save_char(src, '\r');
				}
				else if (peek2(src) == 't')
				{
					next_char(src);
					next_char(src);
					save_char(src, '\t');
				}
				else if (peek2(src) == 'b')
				{
					next_char(src);
					next_char(src);
					save_char(src, '\b');
				}
				else
					save_char(src, next_char(src));
			}
			else if (tokenize_dollar(src, token))
			{

			}
			else
				save_char(src, next_char(src));
		}
		if (peek(src) == EOF)
			token->type = T_ERROR;
		else if (peek(src) == '"')
			next_char(src);
		return (1);
	}
	return (0);
}

int	tokenize_quotes(t_source *src, t_token *token)
{
	if (peek(src) == '\'')
	{
		token->type = T_ID;
		next_char(src);
		while (peek(src) != EOF && peek(src) != '\'')
		{
			if (peek(src) == ESCCHAR)
			{
				if (peek2(src) == ESCCHAR)
				{
					next_char(src);
					save_char(src, next_char(src));
				}
				else if (peek2(src) == '\'')
				{
					next_char(src);
					save_char(src, next_char(src));
				}
				else
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
	return (0);
}

int	tokenize_word(t_source *src, t_token *token)
{
	int	is_wildcard;

	is_wildcard = 0;
	token->type = T_ID;
	while (is_char_word(peek(src)))
	{
		is_wildcard = is_wildcard || (peek(src) == '*');
		if (tokenize_dollar(src, token))
		{

		}
		else if (tokenize_quotes(src, token))
		{

		}
		else if (tokenize_double_quotes(src, token))
		{

		}
		else
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

t_token	*get_next_token(t_source *src)
{
	t_token		*token;

	token = init_token(T_ERROR, NULL);
	if (!token)
		return (NULL);
	skip_comments(src);
	if (tokenize_end_of_file(src, token))
	{

	}
	else if (tokenize_ampersand(src, token))
	{

	}
	else if (tokenize_pipe(src, token))
	{
		
	}
	else if (tokenize_less_than(src, token))
	{

	}
	else if (tokenize_greater_than(src, token))
	{

	}
	else if (tokenize_equals(src, token))
	{
		
	}
	else if (tokenize_semicolon(src, token))
	{
		
	}
	else if (tokenize_backtick(src, token))
	{
		
	}
	else if (tokenize_newline(src, token))
	{
		
	}
	else if (tokenize_word(src, token))
	{
		
	}
	else
		token->type = T_ERROR;

	token->value = ft_strdup(src->str);
	clear_str(src);
	return (token);
}
