CC			= gcc
RM			= rm -rf
# CFLAGS		= -Wall -Wextra -Werror

NAME		= minishell

SRCDIR		= ./src/
OBJDIR		= ./obj/
INCDIR		= ./includes/

SRC			= test_main.c ft_split.c utils_ft.c
OBJ			= $(addprefix $(OBJDIR), $(SRC:.c=.o))

all: $(NAME)

$(OBJDIR)%.o : $(SRCDIR)%.c $(INCDIR)shell.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCDIR)

$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
