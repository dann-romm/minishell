#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "shell.h"

typedef struct s_pipex_data
{
	int	fd1;
	int	fd2;
	int	tube1[2];
	int	tube2[2];
	int	count_running_cmds; // количество команд, завершение которых мы ждём waitpid'ом
}		t_pipex_data;

int		execute(t_command_table *table);
int		exec_builtin(t_command_table *table, t_pipex_data *data, int index);

#endif
