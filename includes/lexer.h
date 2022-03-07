#ifndef LEXER_H
# define LEXER_H

# define ERRCHAR 0
# define ESCCHAR '\\'
# define EOF (-1)

# include <stdlib.h>

typedef struct s_source
{
	char	*buffer;
	int32_t	bufsize;
	int32_t	pos;
	char	*str;
	int32_t	strsize;
	int32_t	strlen;
}	t_source;

typedef enum e_token_type
{
	T_EOF = -1,
	T_ERROR = 0,
	T_NUMBER = 10,
	T_BUILTIN,
	T_ID,
	T_DOLLAR,
	T_STRING,
	T_EXITSTATUS, // $?
	T_IF = 20,
	T_THEN,
	T_ELSE,
	T_ELIF,
	T_FI,
	T_FOR,
	T_IN,
	T_BREAK,
	T_CONTINUE,
	T_WHILE,
	T_DO,
	T_DONE,
	T_AND = 40, // &
	T_ANDAND, // &&
	T_PIPE, // |
	T_OROR, // ||
	T_LESS, // <
	T_GREAT, // >
	T_EQUALS, // =
	T_DGREAT, // >>
	T_DLESS, // <<
	T_LESSAND, // <&
	T_GREATAND, // >&
	T_LESSGREAT, // <>
	T_DLESSDASH, // <<-
	T_CLOBBER, // >|
	T_SEMI, // ;
	T_DSEMI, // ;;
	T_TICK, // `
	T_NEWLINE // \n
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
}	t_token;

typedef struct s_token_list
{
	t_token				*token;
	struct s_token_list	*next;
}	t_token_list;

// source.c
t_source		*init_source(char *str);
char			peek(t_source *src);
char			peek2(t_source *src);
char			next_char(t_source *src);
void			unget_char(t_source *src);
void			skip_whitespaces(t_source *src);
void			save_char(t_source *src, char c);
void			clear_str(t_source *src);

// lexer.c
t_token			*get_next_token(t_source *src);
t_token			*init_token(t_token_type type, char *str);

// token.c
t_token_list	*token_list_init(t_token *token);
int				token_list_push_front(t_token_list **head, t_token_list *node);
int				token_list_clear(t_token_list **head);

#endif
