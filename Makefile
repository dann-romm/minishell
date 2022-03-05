CC						= gcc
RM						= rm -rf
# CFLAGS					= -Wall -Wextra -Werror

NAME					= minishell
LIBS					= -lreadline -lncurses

SRCDIR					= ./src
HASHTABLE_SRCDIR		= $(SRCDIR)/hashtable

OBJDIR					= ./build
HASHTABLE_OBJDIR		= $(OBJDIR)/hashtable

INCDIR					= ./includes

HASHTABLE_SRC			=	$(HASHTABLE_SRCDIR)/hashtable.c \
							$(HASHTABLE_SRCDIR)/pair.c \
							$(HASHTABLE_SRCDIR)/hash.c

SRC						=	$(HASHTABLE_SRC) \
							$(SRCDIR)/main.c \
							$(SRCDIR)/lexer.c \
							$(SRCDIR)/source.c \
							$(SRCDIR)/utils_ft.c \
							$(SRCDIR)/prompt.c

OBJ						= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP						= $(OBJ:.o=.d)

all: $(NAME)


$(NAME): $(OBJDIR) $(HASHTABLE_OBJDIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR) -MMD

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(HASHTABLE_OBJDIR):
	mkdir -p $(HASHTABLE_OBJDIR)
# $(OBJDIR):
# 	mkdir -p $(OBJDIR)
# $(OBJDIR):
# 	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re bonus
