#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"

// void	test_init_source()
// {
// 	t_source	*src = init_source("echo \"hello world\"");
// 	printf("%c %c %c %c %c\n", peek(src), peek2(src), next_char(src), next_char(src), peek2(src));
// }

int	main(int argc, char **argv, char **env)
{
	init_shell(env);
	insert_hashtable(g_shell->env_local, "AAA", "abcde");

	// t_command_table *cmd_table;
	// cmd_table = (t_command_table *)malloc(sizeof(t_command_table));
	// cmd_table->commands_num = 1;
	// cmd_table->commands = (t_simple_cmd **)malloc(sizeof(t_simple_cmd *) * cmd_table->commands_num);
	// t_simple_cmd *cmd1;
	// cmd1 = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));

	// cmd1->cmd = ft_strdup("export");
	// cmd1->cmd_args = (char **)malloc(sizeof(char *));
	// cmd1->cmd_args[0] = ft_strdup("AAA");
	// cmd1->args_num = 1;
	// ft_export(cmd1);
	// print_export_ht(g_shell->env_global);

	// cmd1->cmd = ft_strdup("unset");
	// cmd1->cmd_args = (char **)malloc(sizeof(char *));
	// cmd1->cmd_args[0] = ft_strdup("DISPLAY");
	// cmd1->args_num = 1;
	// ft_unset(cmd1);

	ft_exit();
	
	// cmd1->cmd_args[0] = ft_strdup("s;djf;sl");
	// ft_echo(cmd1->cmd_args, cmd1->args_num);
	// _DEBUG_assert_right_hashtable(ht);
	// char **av = (char **)malloc(sizeof(char *) * 2);
	// av = ft_split(argv[2], '=');
	// ft_export(g_shell->env, cmd1, argv[2]);
	// ft_env(g_shell->env);
	// delete_hashtable(&ht);
}
