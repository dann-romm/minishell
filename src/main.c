#include "shell.h"
#include "lexer.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"
#include "parser.h"

char	*token_type_to_str(t_token_type type)
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

void	_DEBUG_print_token_list(t_token_list *list)
{
	t_token_list	*tmp;

	printf("<-------------- DEBUG PRINT TOKEN LIST -------------->\n");
	tmp = list;
	while (tmp)
	{
		_DEBUG_print_token(tmp->token);
		tmp = tmp->next;
	}
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

int	_DEBUG_print_command_table(t_command_table *table)
{
	printf("<-------------- DEBUG PRINT CMD TABLE -------------->\n");
	printf("stdin: %s\n", table->redirect._stdin);
	printf("stdout: %s\n", table->redirect._stdout);
	printf("commands: %d\n", table->commands_num);
	for (int i = 0; i < table->commands_num; i++)
	{
		printf("\t<===== SIMPLE COMMAND =====>\n");
		printf("\tbinary: %s\n", table->commands[i]->cmd);
		printf("\targs (%d):", table->commands[i]->args_num);
		for (int j = 0; j < table->commands[i]->args_num; j++)
			printf(" %s", table->commands[i]->cmd_args[j]);
		printf("\n");
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_token_list	*list;
	t_command_table	*table;

	init_shell();
	while (1)
	{
		input = read_input("");
		list = create_token_list(input);

		// _DEBUG_print_token_list(list);
		table = parser(list);
		_DEBUG_print_command_table(table);

		clear_token_list(&list);
		free(input);
	}
}
