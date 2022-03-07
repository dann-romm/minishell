CC						= gcc
RM						= rm -rf
# CFLAGS					= -Wall -Wextra -Werror

NAME					= minishell
LIBS					= -lreadline -lncurses

SRCDIR					= ./src
HASHTABLE_SRCDIR		= $(SRCDIR)/hashtable
PARSER_SRCDIR			= $(SRCDIR)/parser
LEXER_SRCDIR			= $(SRCDIR)/lexer

OBJDIR					= ./build
HASHTABLE_OBJDIR		= $(OBJDIR)/hashtable
PARSER_OBJDIR			= $(OBJDIR)/parser
LEXER_OBJDIR			= $(OBJDIR)/lexer

INCDIR					= ./includes

HASHTABLE_SRC			=	$(HASHTABLE_SRCDIR)/hashtable.c \
							$(HASHTABLE_SRCDIR)/pair.c \
							$(HASHTABLE_SRCDIR)/hash.c

PARSER_SRC				=	$(PARSER_SRCDIR)/parser.c

LEXER_SRC				=	$(LEXER_SRCDIR)/lexer.c \
							$(LEXER_SRCDIR)/source.c \
							$(LEXER_SRCDIR)/token.c

SRC						=	$(HASHTABLE_SRC) \
							$(LEXER_SRC) \
							$(PARSER_SRC) \
							$(SRCDIR)/main.c \
							$(SRCDIR)/utils_ft.c \
							$(SRCDIR)/prompt.c

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
