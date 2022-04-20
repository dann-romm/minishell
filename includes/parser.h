/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:33:47 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/20 22:33:48 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "shell.h"

// parser.c

t_cmd_block		*parser(t_token **list);

// command_table.c

t_command_table	*create_command_table(t_token **list);
int				delete_simple_cmd(t_simple_cmd **cmd);

// parser_utils.c

int				handle_redirect(t_command_table *table, t_token **list);
int				handle_parse_error(t_command_table *table, t_token **list);

// simple_cmd.c
t_simple_cmd	*get_simple_cmd(t_token *list);

#endif
