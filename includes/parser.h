#ifndef PARSER_H
# define PARSER_H

# include "shell.h"

// parser.c
t_cmd_block		*parser(t_token **list);
t_command_table	*init_command_table(t_token *list);
int				delete_command_table(t_command_table **table);

// simple_cmd.c
t_simple_cmd	*get_simple_cmd(t_token *list);
int				delete_simple_cmd(t_simple_cmd **cmd);

#endif
