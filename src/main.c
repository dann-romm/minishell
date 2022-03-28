#include "shell.h"
#include "lexer.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"
#include "parser.h"
#include "executor.h"
#include "debug.h"

void	init_shell(char **env)
{
	g_shell = (t_shell *)malloc(sizeof(t_shell));
	if (!g_shell)
	{
		errno = ENOMEM;
		exit(errno);
	}
	g_shell->env_global = init_hashtable(10);
	g_shell->env_local = init_hashtable(10);
	g_shell->exit_status = 0;
	fill_hashtable(env);
}

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_token_list	*list;
	t_command_table	*table = (t_command_table *)malloc(sizeof(t_command_table));

	init_shell(env);

	setting_signal();

	while (1)
	{
		input = read_input("");
		if (input)
			add_history(input);
		list = create_token_list(input);

		// _DEBUG_print_token_list(list);
		table = parser(&list);
		_DEBUG_print_command_table(table);

		if (table)
			execute(table);

		delete_token_list(&list);
		delete_command_table(&table);
		free(input);
	}

	// printf("start\n");
	// pid_t	pid;
	// int fd1 = 0;
	// int fd2 = 1;
	// int tube1[2];
	// int tube2[2];
	// int _saved_stdin;
	// int _saved_stdout;

	// pipe(tube1);
	// pipe(tube2);

	// _saved_stdin = dup(0);
	// _saved_stdout = dup(1);

	// dup2(0, 0);
	// dup2(tube2[1], 1);
	// printf("cmd1\n");

	// dup2(_saved_stdin, 0);
	// dup2(_saved_stdout, 1);
	
	// close(tube1[0]);
	// close(tube1[1]);
	// tube1[0] = tube2[0];
	// tube1[1] = tube2[1];
	// pipe(tube2);

	// dup2(0, 0);
	// dup2(1, 1);

	// if ((pid = fork()) == 0)
	// {
	// 	char buf[6];

	// 	dup2(tube1[0], 0);
	// 	dup2(1, 1);

	// 	close(tube1[0]);
	// 	close(tube1[1]);
	// 	close(tube2[0]);
	// 	close(tube2[1]);

	// 	read(0, buf, 5);
	// 	buf[5] = 0;
	// 	printf("%s", buf);
	// 	printf("cmd2\n");

	// 	exit(0);
	// }

	// close(tube1[0]);
	// close(tube1[1]);
	// tube1[0] = tube2[0];
	// tube1[1] = tube2[1];
	
	// close(tube1[0]);
	// close(tube1[1]);
}
