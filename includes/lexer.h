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
	T_BACKTICK, // `
	T_NEWLINE // \n
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

// source.c
char			peek(t_source *src);
char			peek2(t_source *src);
char			next_char(t_source *src);
void			unget_char(t_source *src);
void			save_char(t_source *src, char c);

// source_utils.c
t_source		*init_source(char *str);
void			delete_source(t_source **src);
void			reallocate_str(t_source *src);
void			skip_whitespaces(t_source *src);
void			clear_str(t_source *src);

// lexer.c
t_token			*get_next_token(t_source *src);

// token.c
t_token			*init_token(t_token_type type, char *str);
int				delete_token(t_token **token);
t_token			*create_token_list(char *input);
int				push_back_token_list(t_token **head, t_token *node);
int				remove_token_list(t_token **head, t_token **node);
int				delete_token_list(t_token **head);

// wildcard.c
int				handle_wildcard(t_source *src, t_token **token);

#endif
