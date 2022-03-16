#include "shell.h"
#include "lexer.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"
#include "parser.h"
#include "debug.h"

void	init_shell(char **env)
{
	g_shell = (t_shell *)malloc(sizeof(t_shell));
	g_shell->env_global = init_hashtable(10);
	g_shell->env_local = init_hashtable(10);
	fill_hashtable(env);
}

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_token_list	*list;
	t_command_table	*table;

	init_shell(env);
	while (1)
	{
		input = read_input("");
		list = create_token_list(input);

		_DEBUG_print_token_list(list);
		// table = parser(list);
		// _DEBUG_print_command_table(table);

		clear_token_list(&list);
		free(input);
	}

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
