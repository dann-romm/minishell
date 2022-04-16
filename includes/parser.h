#ifndef PARSER_H
# define PARSER_H

# include "shell.h"

typedef enum e_cmd_block_delimiter
{
	CMDBL_END,
	CMDBL_AND,
	CMDBL_OR,
	CMDBL_SEMI
}	t_cmd_block_delimiter;

typedef struct s_cmd_block
{
	t_command_table			*table; // array of t_command_table structures
	t_cmd_block_delimiter	delimiter;
}	t_cmd_block;

// parser.c
t_cmd_block		*parser(t_token **list);
t_command_table	*init_command_table(t_token *list);
int				delete_command_table(t_command_table **table);

// simple_cmd.c
t_simple_cmd	*get_simple_cmd(t_token *list);
int				delete_simple_cmd(t_simple_cmd **cmd);

#endif
