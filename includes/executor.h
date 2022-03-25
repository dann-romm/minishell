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
char	*find_path(t_simple_cmd *command);
char	**ht_to_array(t_hashtable *ht);

#endif
