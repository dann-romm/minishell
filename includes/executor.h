#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "shell.h"

typedef struct s_pipex_data
{
	int		fd1;
	int		fd2;
	int		_saved_stdin;
	int		_saved_stdout;
	int		tube1[2];
	int		tube2[2];
	int		count_running_cmds;
}		t_pipex_data;

int	execute(t_cmd_block *cmd_block);

#endif
