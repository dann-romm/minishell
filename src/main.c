#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"

// void	test_init_source()
// {
// 	t_source	*src = init_source("echo \"hello world\"");
// 	printf("%c %c %c %c %c\n", peek(src), peek2(src), next_char(src), next_char(src), peek2(src));
// }

char	*_DEBUG_token_type_to_str(t_token_type type)
{
	switch (type)
	{
		case T_EOF:
			return ("T_EOF");
		case T_ERROR:
			return ("T_ERROR");
		case T_NUMBER:
			return ("T_NUMBER");
		case T_ID:
			return ("T_ID");
		case T_DOLLAR:
			return ("T_DOLLAR");
		case T_STRING:
			return ("T_STRING");
		case T_BUILTIN:
			return ("T_BUILTIN");
		case T_EXITSTATUS:
			return ("T_EXITSTATUS");
		case T_IF:
			return ("T_IF");
		case T_THEN:
			return ("T_THEN");
		case T_ELSE:
			return ("T_ELSE");
		case T_ELIF:
			return ("T_ELIF");
		case T_FI:
			return ("T_FI");
		case T_FOR:
			return ("T_FOR");
		case T_IN:
			return ("T_IN");
		case T_BREAK:
			return ("T_BREAK");
		case T_CONTINUE:
			return ("T_CONTINUE");
		case T_WHILE:
			return ("T_WHILE");
		case T_DO:
			return ("T_DO");
		case T_DONE:
			return ("T_DONE");
		case T_AND:
			return ("T_AND");
		case T_ANDAND:
			return ("T_ANDAND");
		case T_PIPE:
			return ("T_PIPE");
		case T_OROR:
			return ("T_OROR");
		case T_LESS:
			return ("T_LESS");
		case T_GREAT:
			return ("T_GREAT");
		case T_EQUALS:
			return ("T_EQUALS");
		case T_DGREAT:
			return ("T_DGREAT");
		case T_DLESS:
			return ("T_DLESS");
		case T_LESSAND:
			return ("T_LESSAND");
		case T_GREATAND:
			return ("T_GREATAND");
		case T_LESSGREAT:
			return ("T_LESSGREAT");
		case T_DLESSDASH:
			return ("T_DLESSDASH");
		case T_CLOBBER:
			return ("T_CLOBBER");
		case T_SEMI:
			return ("T_SEMI");
		case T_DSEMI:
			return ("T_DSEMI");
		case T_TICK:
			return ("T_TICK");
		case T_NEWLINE:
			return ("T_NEWLINE");
		default:
			return ("(null)");
	}
}

void	_DEBUG_print_token(t_token *token)
{	
	printf("token:\n   type:  %s\n   value: %s\n", _DEBUG_token_type_to_str(token->type), token->value);
}

int	_DEBUG_assert_right_hashtable(t_hashtable *ht)
{
	uint32_t	index;
	t_pair		*pair;

	index = -1;
	while (++index < ht->size)
	{
		pair = ht->table[index];
		while (pair)
		{
			if (ht->hash(pair->key, ht->size) != index)
			{
				printf("ERROR: (%u) hash at index %u\n", ht->hash(pair->key, ht->size), index);
				exit(1);
			}
			pair = pair->next;
		}
	}
	return (0);
}

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
	// printf("%s\n", argv[2]);
	t_command_table *cmd_table;
	cmd_table = (t_command_table *)malloc(sizeof(t_command_table));
	cmd_table->commands_num = 1;
	cmd_table->commands = (t_simple_cmd **)malloc(sizeof(t_simple_cmd *) * cmd_table->commands_num);
	t_simple_cmd *cmd1;
	cmd1 = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	// // printf("pwd then: ");
	// // ft_pwd(ht);
	cmd1->cmd = ft_strdup("export");
	cmd1->cmd_args = (char **)malloc(sizeof(char *));
	cmd1->cmd_args = ft_split(argv[2], ' ');
	printf("%s %s\n", cmd1->cmd_args[0], cmd1->cmd_args[1]);

	
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
