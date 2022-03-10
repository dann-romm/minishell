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
	// char		*input;
	// t_source	*src;
	// t_token		*token;

	// while (1)
	// {
	// 	input = read_input("");
	// 	src = init_source(input);

	// 	token = get_next_token(src);
	// 	while (token->type != T_EOF)
	// 	{
	// 		_DEBUG_print_token(token);
	// 		free(token->value);
	// 		free(token);
	// 		token = get_next_token(src);
	// 	}
	// 	free(token->value);
	// 	free(token);
	// 	free(src->buffer);
	// 	free(src->str);
	// 	free(src);
	// 	if (ft_strcmp(input, "exit") == 0)
	// 	{
	// 		free(input);
	// 		break;
	// 	}
	// 	free(input);
	// }

	init_shell(env);
	// insert_hashtable(g_shell->env_local, "AAA", "abcde");

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
	if (argv[1])
		ft_env();
	else
	{
		insert_hashtable(g_shell->env_global, "BBB", "abcde");
		print_ht(g_shell->env_global);
	}
	
	// cmd1->args_num = 2;
	// cmd1->cmd_args[0] = ft_strdup("123");
	// cmd1->cmd_args[1] = ft_strdup("abc");
	// // ft_cd(ht, cmd1);
	// // printf("pwd now: ");
	// // ft_pwd(ht);
	// ft_cd(ht, cmd1);
	// printf("pwd now: ");
	// ft_pwd(ht);
	// printf("oldpwd now: %s\n\n", find_hashtable(ht, "OLDPWD"));
	// cmd1->cmd_args[0] = ft_strdup("-");
	// // ft_cd(ht, cmd1);
	// // printf("pwd now: ");
	// // ft_pwd(ht);
	// // printf("oldpwd now: %s\n\n", find_hashtable(ht, "OLDPWD"));
	// cmd1->cmd_args[0] = ft_strdup("/Users/mgwyness/Desktop/minishell");
	// ft_cd(ht, cmd1);
	// printf("pwd now: ");
	// ft_pwd(ht);
	// printf("oldpwd now: %s\n\n", find_hashtable(ht, "OLDPWD"));
	// cmd1->cmd_args[0] = ft_strdup("-");
	// ft_cd(ht, cmd1);
	// printf("pwd now: ");
	// ft_pwd(ht);
	// printf("oldpwd now: %s\n\n", find_hashtable(ht, "OLDPWD"));
	// cmd1->cmd_args[0] = ft_strdup("234vnf");
	// ft_cd(ht, cmd1);

	// cmd1->cmd_args[0] = ft_strdup("s;djf;sl");
	// ft_echo(cmd1->cmd_args, cmd1->args_num);
	// _DEBUG_assert_right_hashtable(ht);
	// char **av = (char **)malloc(sizeof(char *) * 2);
	// av = ft_split(argv[2], '=');
	// ft_export(g_shell->env, cmd1, argv[2]);
	// ft_env(g_shell->env);
	// delete_hashtable(&ht);
}
