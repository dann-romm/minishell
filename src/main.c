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

		table = parser(&list);
		// _DEBUG_print_command_table(table);

		if (table)
			execute(table);

		delete_token_list(&list);
		delete_command_table(&table);
		free(input);
	}

	// ft_pwd();
	// table->commands_num = 1;
	// t_simple_cmd *cmd1 = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	// cmd1->cmd = ft_strdup("ls");
	// cmd1->args_num = 1;
	// cmd1->cmd_args = (char **)malloc(sizeof(char *));
	// cmd1->cmd_args[0] = ft_strdup("la");
	// printf("%s\n", find_path(cmd1));
	// execute(table);
	// ft_pwd();
	// // printf("\n\n");
	// ft_env();
	// printf("\n\n");
	// cmd1->cmd = ft_strdup("cd");
	// cmd1->args_num = 1;
	// ft_cd(cmd1);
	// // ft_pwd();
	// ft_env();
	// cmd1->cmd = ft_strdup("unset");
	// cmd1->cmd_args = (char **)malloc(sizeof(char *));
	// cmd1->cmd_args[0] = ft_strdup("DISPLAY");
	// cmd1->args_num = 1;
	// ft_unset(cmd1);
	// ft_exit();
	
	// cmd1->cmd_args[0] = ft_strdup("s;djf;sl");
	// ft_echo(cmd1->cmd_args, cmd1->args_num);
	// _DEBUG_assert_right_hashtable(ht);
	// char **av = (char **)malloc(sizeof(char *) * 2);
	// av = ft_split(argv[2], '=');
	// ft_export(g_shell->env, cmd1, argv[2]);
	// ft_env(g_shell->env);
	// delete_hashtable(&ht);
}
