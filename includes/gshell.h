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

t_shell	*g_shell;

void	delete_shell(void);

#endif
