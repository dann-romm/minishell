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

int	is_word_char(char c)
{
	return (is_alnum(c)
		|| (c == '_')
		|| (c == '-')
		|| (c == '.')
		|| (c == '/')
		|| (c == '?')
		|| (c == '!')
		|| (c == '*')
		|| (c == '@')
		|| (c == '#')
		|| (c == '%')
		|| (c == '^')
		|| (c == '&')
		|| (c == '(')
		|| (c == ')')
		|| (c == '[')
		|| (c == ']')
		|| (c == '~')
		|| (c == '+'));
}

void	put_exit_status_into_src(t_source *src)
{
	const char	*exit_status = ft_itoa(g_shell->exit_status);
	int			i;

	printf("exit_status = %s\n", exit_status);
	if (!exit_status)
		return ; // error
	i = 0;
	while (exit_status[i])
		save_char(src, exit_status[i++]);
}

void	put_env_into_src(t_source *src)
{
	char	*key;
	char	*value;

	while (is_alnum(peek(src)) || peek(src) == '_')
		save_char(src, next_char(src));
	key = ft_strdup(src->str);
	value = find_hashtable(g_shell->env_global, key);
	clear_str(src);
	while (value && *value)
		save_char(src, *value++);
	free(key);
}

t_token	*get_next_token(t_source *src)
{
	t_token		*token;
	int			is_wildcard;
	int			require_bracket;

	token = init_token(T_ERROR, NULL);
	if (!token)
		return (NULL);
	skip_comments(src);
	if (peek(src) == '&')
	{
		token->type = T_AND;
		save_char(src, next_char(src));
		if (peek(src) == '&')
		{
			token->type = T_ANDAND;
			save_char(src, next_char(src));
		}
	}
	else if (peek(src) == '|')
	{
		token->type = T_PIPE;
		save_char(src, next_char(src));
		if (peek(src) == '|')
		{
			token->type = T_OROR;
			save_char(src, next_char(src));
		}
	}
	else if (peek(src) == '<')
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
	}
	else if (peek(src) == '>')
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
	}
	else if (peek(src) == '=')
	{
		token->type = T_EQUALS;
		save_char(src, next_char(src));
	}
	else if (peek(src) == ';')
	{
		token->type = T_SEMI;
		save_char(src, next_char(src));
		if (peek(src) == ';')
		{
			token->type = T_DSEMI;
			save_char(src, next_char(src));
		}
	}
	else if (peek(src) == '`')
	{
		token->type = T_TICK;
		save_char(src, next_char(src));
	}
	else if (peek(src) == '\n')
	{
		token->type = T_NEWLINE;
		save_char(src, next_char(src));
	}
	else if (peek(src) == EOF || peek(src) == '\0')
	{
		token->type = T_EOF;
		save_char(src, '\0');
		next_char(src);
	}
	else if (peek(src) == '$')
	{
		require_bracket = 0;
		next_char(src);
		if (peek(src) == '?')
		{
			next_char(src);
			put_exit_status_into_src(src);
			token->type = T_ID;
		}
		else
		{
			if (peek(src) == '{')
			{
				require_bracket = 1;
				next_char(src);
			}
			put_env_into_src(src); // TODO: special parameter https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html#tag_18_06_02
			if (require_bracket && peek(src) != '}')
				token->type = T_ERROR;
			else if (require_bracket)
				next_char(src);
			token->type = T_ID;
		}
	}
	else if (peek(src) == '"')
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
			else if (peek(src) == '$')
			{
				next_char(src);
				put_env_into_src(src);
			}
			else
				save_char(src, next_char(src));
		}
		if (peek(src) == EOF)
			token->type = T_ERROR;
		else if (peek(src) == '"')
			next_char(src);
	}
	else if (peek(src) == '`')
	{
		next_char(src);
		while (peek(src) != EOF && peek(src) != '`')
			save_char(src, next_char(src));
		token->type = T_TICK;
		if (peek(src) == EOF)
			token->type = T_ERROR;
		else
			next_char(src);
	}
	else if (peek(src) == '\'')
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
	}
	else if (is_word_char(peek(src)))
	{
		is_wildcard = 0;
		token->type = T_ID;
		while (is_word_char(peek(src)))
		{
			is_wildcard = is_wildcard || (peek(src) == '*');
			save_char(src, next_char(src));
		}
		if (is_wildcard)
			return (handle_wildcard(src, token));
	}
	else
		token->type = T_ERROR;

	token->value = ft_strdup(src->str);
	clear_str(src);
	return (token);
}
