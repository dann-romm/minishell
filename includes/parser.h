#ifndef PARSER_H
# define PARSER_H

// parser.c
t_command_table	*parser(t_token_list **list);

// simple_cmd.c
t_simple_cmd	*get_simple_cmd(t_token_list *list);

#endif
