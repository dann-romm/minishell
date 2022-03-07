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
							$(LEXER_SRCDIR)/source.c

SRC						=	$(HASHTABLE_SRC) \
							$(LEXER_SRC) \
							$(PARSER_SRC) \
							$(SRCDIR)/main.c \
							$(SRCDIR)/utils_ft.c \
							$(SRCDIR)/prompt.c

OBJ						= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP						= $(OBJ:.o=.d)

all: $(NAME)


$(NAME): $(OBJDIR) $(HASHTABLE_OBJDIR) $(PARSER_OBJDIR) $(LEXER_OBJDIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR) -MMD

$(OBJDIR):
	mkdir -p $@
$(HASHTABLE_OBJDIR):
	mkdir -p $@
$(PARSER_OBJDIR):
	mkdir -p $@
$(LEXER_OBJDIR):
	mkdir -p $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re bonus
