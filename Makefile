CC						= gcc
RM						= rm -rf
# CFLAGS					= -Wall -Wextra -Werror

NAME					= minishell
LIBS					= -lreadline -lncurses

SRCDIR					= ./src
HASHTABLE_SRCDIR		= $(SRCDIR)/hashtable
BUILTIN_SRCDIR			= $(SRCDIR)/builtin

OBJDIR					= ./build
HASHTABLE_OBJDIR		= $(OBJDIR)/hashtable
BUILTIN_OBJDIR			= $(OBJDIR)/builtin

INCDIR					= ./includes

HASHTABLE_SRC			=	$(HASHTABLE_SRCDIR)/hashtable.c \
							$(HASHTABLE_SRCDIR)/pair.c \
							$(HASHTABLE_SRCDIR)/hash.c

BUILTIN_SRC				=	$(BUILTIN_SRCDIR)/builtin.c \
							$(BUILTIN_SRCDIR)/cd.c \
							$(BUILTIN_SRCDIR)/echo.c \
							$(BUILTIN_SRCDIR)/env.c \
							$(BUILTIN_SRCDIR)/exit.c \
							$(BUILTIN_SRCDIR)/export.c \
							$(BUILTIN_SRCDIR)/pwd.c \
							$(BUILTIN_SRCDIR)/unset.c 

SRC						=	$(HASHTABLE_SRC) \
							$(BUILTIN_SRC) \
							$(SRCDIR)/main.c \
							$(SRCDIR)/lexer.c \
							$(SRCDIR)/ft_split.c \
							$(SRCDIR)/executor.c \
							$(SRCDIR)/source.c \
							$(SRCDIR)/utils_ft.c \
							$(SRCDIR)/utils.c \
							$(SRCDIR)/prompt.c

OBJ						= $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DEP						= $(OBJ:.o=.d)

all: $(NAME)


$(NAME): $(OBJDIR) $(HASHTABLE_OBJDIR) $(BUILTIN_OBJDIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LIBS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR) -MMD

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(HASHTABLE_OBJDIR):
	mkdir -p $(HASHTABLE_OBJDIR)

$(BUILTIN_OBJDIR):
	mkdir -p $(BUILTIN_OBJDIR)

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
