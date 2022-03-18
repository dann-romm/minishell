#ifndef PARSER_H
# define PARSER_H

// parser.c
t_command_table	*parser(t_token_list **list);
t_command_table	*init_command_table(t_token_list *list);
int				delete_command_table(t_command_table **table);

// simple_cmd.c
t_simple_cmd	*get_simple_cmd(t_token_list *list);
int				delete_simple_cmd(t_simple_cmd **cmd);

#endif
