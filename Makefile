CC						= gcc
RM						= rm -rf
CFLAGS					= -MMD
# CFLAGS					= -Wall -Wextra -Werror -MMD

NAME					= minishell
READLINE				= ./lib/libhistory.a ./lib/libreadline.a

SRCDIR					= ./src
BUILTIN_SRCDIR			= $(SRCDIR)/builtin
EXECUTOR_SRCDIR			= $(SRCDIR)/executor
HASHTABLE_SRCDIR		= $(SRCDIR)/hashtable
LEXER_SRCDIR			= $(SRCDIR)/lexer
PARSER_SRCDIR			= $(SRCDIR)/parser
PROMPT_SRCDIR			= $(SRCDIR)/prompt
UTILS_SRCDIR			= $(SRCDIR)/utils
HISTORY_SRCDIR			= $(SRCDIR)/history
SIGNAL_SRCDIR			= $(SRCDIR)/signal
FORK_SRCDIR				= $(SRCDIR)/fork
PIPE_SRCDIR				= $(SRCDIR)/pipe

OBJDIR					= ./build
BUILTIN_OBJDIR			= $(OBJDIR)/builtin
EXECUTOR_OBJDIR			= $(OBJDIR)/executor
HASHTABLE_OBJDIR		= $(OBJDIR)/hashtable
LEXER_OBJDIR			= $(OBJDIR)/lexer
PARSER_OBJDIR			= $(OBJDIR)/parser
PROMPT_OBJDIR			= $(OBJDIR)/prompt
UTILS_OBJDIR			= $(OBJDIR)/utils
HISTORY_OBJDIR			= $(OBJDIR)/history
SIGNAL_OBJDIR			= $(OBJDIR)/signal
PIPE_OBJDIR				= $(OBJDIR)/pipe
FORK_OBJDIR				= $(OBJDIR)/fork

INCDIR					= ./includes

BUILTIN_SRC				=	$(BUILTIN_SRCDIR)/assignment.c \
							$(BUILTIN_SRCDIR)/cd.c \
							$(BUILTIN_SRCDIR)/echo.c \
							$(BUILTIN_SRCDIR)/env.c \
							$(BUILTIN_SRCDIR)/exit.c \
							$(BUILTIN_SRCDIR)/export.c \
							$(BUILTIN_SRCDIR)/pwd.c \
							$(BUILTIN_SRCDIR)/unset.c

EXECUTOR_SRC			=	$(EXECUTOR_SRCDIR)/executor.c

HASHTABLE_SRC			=	$(HASHTABLE_SRCDIR)/hashtable.c \
							$(HASHTABLE_SRCDIR)/pair.c \
							$(HASHTABLE_SRCDIR)/hash.c \
							$(HASHTABLE_SRCDIR)/fill_hashtable.c

LEXER_SRC				=	$(LEXER_SRCDIR)/lexer.c \
							$(LEXER_SRCDIR)/source.c \
							$(LEXER_SRCDIR)/token.c \
							$(LEXER_SRCDIR)/wildcard.c

PARSER_SRC				=	$(PARSER_SRCDIR)/parser.c \
							$(PARSER_SRCDIR)/simple_cmd.c

PROMPT_SRC				=	$(PROMPT_SRCDIR)/prompt.c

UTILS_SRC				=	$(UTILS_SRCDIR)/ft_split.c \
							$(UTILS_SRCDIR)/utils_ft.c

HISTORY_SRC				=	$(HISTORY_SRCDIR)/history.c

SIGNAL_SRC				=	$(SIGNAL_SRCDIR)/signal.c

PIPE_SRC				=	$(PIPE_SRCDIR)/pipe.c

FORK_SRC				=	$(FORK_SRCDIR)/fork.c

SRC						=	$(BUILTIN_SRC) \
							$(EXECUTOR_SRC) \
							$(FORK_SRC) \
							$(PIPE_SRC) \
							$(HASHTABLE_SRC) \
							$(LEXER_SRC) \
							$(PARSER_SRC) \
							$(PROMPT_SRC) \
							$(UTILS_SRC) \
							$(HISTORY_SRC) \
							$(SIGNAL_SRC) \
							$(SRCDIR)/main.c \

OBJ						= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP						= $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(READLINE) -ltermcap -o $(NAME)

$(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

test: all
	./minishell

norm:
	norminette $(SRCDIR) 

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re bonus
