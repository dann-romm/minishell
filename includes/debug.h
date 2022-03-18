#ifndef DEBUG_H
# define DEBUG_H

# include "hashtable.h"
# include "lexer.h"
# include "shell.h"

__attribute__((weak)) char	*_DEBUG_token_type_to_str(t_token_type type)
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

__attribute__((weak)) char	*_DEBUG_cmd_type_to_str(t_cmd_type type)
{
	switch (type)
	{
		case CMD_NONE:
			return ("CMD_NONE");
		case CMD_ASSIGNMENT:
			return ("CMD_ASSIGNMENT");
		case CMD_CD:
			return ("CMD_CD");
		case CMD_ECHO:
			return ("CMD_ECHO");
		case CMD_ENV:
			return ("CMD_ENV");
		case CMD_EXIT:
			return ("CMD_EXIT");
		case CMD_EXPORT:
			return ("CMD_EXPORT");
		case CMD_PWD:
			return ("CMD_PWD");
		case CMD_UNSET:
			return ("CMD_UNSET");
		default:
			return ("(null)");
	}
}

__attribute__((weak)) void	_DEBUG_print_token(t_token *token)
{
	if (!token)
	{
		printf("token is NULL\n");
		return ;
	}
	printf("token:\n   type:  %s\n   value: %s\n", _DEBUG_token_type_to_str(token->type), token->value);
}

__attribute__((weak)) void	_DEBUG_print_token_list(t_token_list *list)
{
	t_token_list	*tmp;

	printf("<-------------- DEBUG PRINT TOKEN LIST -------------->\n");
	if (!list)
	{
		printf("token list is NULL\n");
		return ;
	}
	tmp = list;
	while (tmp)
	{
		_DEBUG_print_token(tmp->token);
		tmp = tmp->next;
	}
}

__attribute__((weak)) int	_DEBUG_assert_right_hashtable(t_hashtable *ht)
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

__attribute__((weak)) int	_DEBUG_print_command_table(t_command_table *table)
{
	printf("<-------------- DEBUG PRINT CMD TABLE -------------->\n");
	if (!table)
	{
		printf("table is NULL\n");
		return (0);
	}
	printf("is_append: %d | stdin file:  %s\n", table->redirect.is_stdin_append, table->redirect._stdin);
	printf("is_append: %d | stdout file: %s\n", table->redirect.is_stdout_append, table->redirect._stdout);
	printf("commands: %d\n", table->commands_num);
	for (int i = 0; i < table->commands_num; i++)
	{
		printf("\t<===== SIMPLE COMMAND =====>\n");
		if (table->commands[i])
		{
			printf("\tbinary: %s\n", table->commands[i]->cmd);
			printf("\ttype: %s\n", _DEBUG_cmd_type_to_str(table->commands[i]->type));
			printf("\targs (%d):", table->commands[i]->args_num);
			for (int j = 0; j < table->commands[i]->args_num; j++)
				printf(" %s", table->commands[i]->cmd_args[j]);
			printf("\n");
		}
		else
			printf("\tsimple cmd is NULL\n");
	}
	return (0);
}

__attribute__((weak)) void	_DEBUG_print_hashtable(t_hashtable *ht)
{
	t_pair	*pair;
	int		i;

	i = -1;
	printf("HASHTABLE: size=%d, count=%d, load_ratio=%.3f\n", ht->size, ht->count, (float)ht->count / ht->size);
	while (++i < ht->size)
	{
		pair = ht->table[i];
		printf("table[%d]", i);
		while (pair)
		{
			printf(" -> (%s; %s)", pair->key, pair->value);
			pair = pair->next;
		}
		printf("\n");
	}
	printf("\n");
}

#endif
