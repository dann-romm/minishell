CC						= gcc
RM						= rm -rf
# CFLAGS					= -Wall -Wextra -Werror

NAME					= minishell
LIBS					= -lreadline -lncurses

SRCDIR					= ./src
BUILTIN_SRCDIR			= $(SRCDIR)/builtin
EXECUTOR_SRCDIR			= $(SRCDIR)/executor
HASHTABLE_SRCDIR		= $(SRCDIR)/hashtable
LEXER_SRCDIR			= $(SRCDIR)/lexer
PARSER_SRCDIR			= $(SRCDIR)/parser
PROMPT_SRCDIR			= $(SRCDIR)/prompt
UTILS_SRCDIR			= $(SRCDIR)/utils

OBJDIR					= ./build
BUILTIN_OBJDIR			= $(OBJDIR)/builtin
EXECUTOR_OBJDIR			= $(OBJDIR)/executor
HASHTABLE_OBJDIR		= $(OBJDIR)/hashtable
LEXER_OBJDIR			= $(OBJDIR)/lexer
PARSER_OBJDIR			= $(OBJDIR)/parser
PROMPT_OBJDIR			= $(OBJDIR)/prompt
UTILS_OBJDIR			= $(OBJDIR)/utils

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
							$(LEXER_SRCDIR)/token.c

PARSER_SRC				=	$(PARSER_SRCDIR)/parser.c \
							$(PARSER_SRCDIR)/simple_cmd.c

PROMPT_SRC				=	$(PROMPT_SRCDIR)/prompt.c

UTILS_SRC				=	$(UTILS_SRCDIR)/ft_split.c \
							$(UTILS_SRCDIR)/utils_ft.c

SRC						=	$(BUILTIN_SRC) \
							$(EXECUTOR_SRC) \
							$(HASHTABLE_SRC) \
							$(LEXER_SRC) \
							$(PARSER_SRC) \
							$(PROMPT_SRC) \
							$(UTILS_SRC) \
							$(SRCDIR)/main.c \

OBJ						= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP						= $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR) -MMD

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re bonus
