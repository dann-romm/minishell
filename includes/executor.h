#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "shell.h"

typedef struct s_pipex_data
{
	int	fd1;
	int	fd2;
	int	tube1[2];
	int	tube2[2];
}		t_pipex_data;

int		execute(t_command_table *table);

#endif
