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
			scan_word(src);
			if (require_bracket && peek(src) != '}')
				token->type = T_ERROR;
			else if (require_bracket)
				next_char(src);
			token->type = T_DOLLAR;
		}
	}




	token->value = ft_strdup(src->str);
	clear_str(src);
	return (token);
}

// t_token_list	*init_token_list_node(t_token *token)
// {
// 	t_token_list	*list = (t_token_list *)malloc(sizeof(t_token_list));
	
// 	if (!list)
// 	{
// 		errno = ENOMEM;
// 		return (NULL);
// 	}
// 	list->token = token;
// 	list->next = NULL;
// 	return (list);
// }

// void	token_list_push_front(t_token_list **list, t_token *token)
// {
// 	t_token_list	*node;

// 	if (!list || !(*list))
// 		return ;
// 	node = init_token_list_node(token);
// 	if (!node)
// 		return ;
// 	node->next = *list;
// 	*list = node;
// }

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
