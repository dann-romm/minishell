#include "lexer.h"
#include "libft_funcs.h"
#include "shell.h"

t_token	*init_token(t_token_type type, char *str)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
	{
		errno = ENOMEM;
		return (NULL);
	}
	token->type = type;
	if (str)
		token->value = ft_strdup(str);
	else
		token->value = NULL;
	if (str && !token->value)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (token);
}

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
		|| (c == '@')
		|| (c == '#')
		|| (c == '%')
		|| (c == '^')
		|| (c == '&')
		|| (c == '(')
		|| (c == ')')
		|| (c == '[')
		|| (c == ']')
		|| (c == '+'));
}

void	scan_word(t_source *src)
{
	while (is_word_char(peek(src)))
		save_char(src, next_char(src));
}

void	put_env_into_src(t_source *src)
{
	char	*key;
	char	*value;
	int		key_len;

	key_len = 0;
	while (is_alnum(peek(src)) || peek(src) == '_')
	{
		key_len++;
		next_char(src);
	}
	key = (char *)malloc(sizeof(char) * (key_len + 1));
	while (key_len--)
		unget_char(src);
	while (is_alnum(peek(src)) || peek(src) == '_')
		key[++key_len] = next_char(src);
	key[++key_len] = '\0';
	value = find_hashtable(g_shell->env_global, key);
	while (value && *value)
		save_char(src, *value++);
	free(key);
}

t_token	*get_next_token(t_source *src)
{
	t_token		*token;
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
			token->type = T_EXITSTATUS;
			save_char(src, next_char(src));
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
			// token->type = T_DOLLAR;
			token->type = T_STRING;
		}
	}
	else if (peek(src) == '"')
	{
		token->type = T_STRING;
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
		token->type = T_STRING;
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
		int			i;
		const char	*builtins[7] = {"echo", "cd", "pwd", "export", "unset", "env", "exit"};
		token->type = T_ID;
		scan_word(src);
		
		i = 0;
		while (i < 7)
		{
			if (!ft_strcmp(src->str, (char *)builtins[i]))
				token->type = T_BUILTIN;
			i++;
		}
	}
	else
		token->type = T_ERROR;

	token->value = ft_strdup(src->str);
	clear_str(src);
	return (token);
}
