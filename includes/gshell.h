/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gshell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:36:43 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/22 20:36:44 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GSHELL_H
# define GSHELL_H

# include "hashtable.h"
# include "parser.h"
# include "lexer.h"

typedef struct s_shell
{
	t_hashtable	*env_global;
	t_hashtable	*env_local;
	int32_t		exit_status;
	t_cmd_block	*cmd_blocks;
	t_token		*list;
}	t_shell;

t_shell	g_shell;

int	delete_shell(void);

#endif
