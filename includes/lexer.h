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
int				unget_char(t_source *src);
int				save_char(t_source *src, char c);

// source_utils.c
t_source		*init_source(char *str);
int				delete_source(t_source **src);
int				reallocate_str(t_source *src);
int				skip_whitespaces(t_source *src);
int				clear_str(t_source *src);

// lexer.c
t_token			*lexer(char *input);

// get_next_token.c
t_token			*get_next_token(t_source *src);
void			skip_comments(t_source *src);
int				tokenize_end_of_line(t_source *src, t_token *token);
int				tokenize_pipe(t_source *src, t_token *token);
int				tokenize_tilde(t_source *src, t_token *token);

// tokenize_dollar.c
int				tokenize_dollar(t_source *src, t_token *token);

// tokenize_word.c
int				tokenize_word(t_source *src, t_token *token);

// token.c
t_token			*init_token(t_token_type type, char *str);
int				delete_token(t_token **token);
int				push_back_token_list(t_token **head, t_token *node);
int				remove_token_list(t_token **head, t_token **node);
int				delete_token_list(t_token **head);

// wildcard.c
void			handle_wildcard(t_source *src, t_token **token);

#endif
