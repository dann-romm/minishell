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
		dprintf(2, "token is NULL\n");
		return ;
	}
	dprintf(2, "token:\n   type:  %s\n   value: %s\n", _DEBUG_token_type_to_str(token->type), token->value);
}

__attribute__((weak)) void	_DEBUG_print_token_list(t_token *list)
{
	t_token	*tmp;

	dprintf(2, "<-------------- DEBUG PRINT TOKEN LIST -------------->\n");
	if (!list)
	{
		dprintf(2, "token list is NULL\n");
		return ;
	}
	tmp = list;
	while (tmp)
	{
		_DEBUG_print_token(tmp);
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
				dprintf(2, "ERROR: (%u) hash at index %u\n", ht->hash(pair->key, ht->size), index);
				exit(1);
			}
			pair = pair->next;
		}
	}
	return (0);
}

__attribute__((weak)) void	_DEBUG_print_command_table(t_command_table *table)
{
	dprintf(2, "<-------------- DEBUG PRINT CMD TABLE -------------->\n");
	if (!table)
	{
		dprintf(2, "table is NULL\n");
		return ;
	}
	dprintf(2, "is_append: %d | stdin file:  %s\n", table->redirect.is_stdin_append, table->redirect._stdin);
	dprintf(2, "is_append: %d | stdout file: %s\n", table->redirect.is_stdout_append, table->redirect._stdout);
	dprintf(2, "commands: %d\n", table->commands_num);
	for (int i = 0; i < table->commands_num; i++)
	{
		dprintf(2, "\t<===== SIMPLE COMMAND =====>\n");
		if (table->commands[i])
		{
			dprintf(2, "\tbinary: %s\n", table->commands[i]->cmd);
			dprintf(2, "\ttype: %s\n", _DEBUG_cmd_type_to_str(table->commands[i]->type));
			dprintf(2, "\targs (%d):", table->commands[i]->args_num);
			for (int j = 0; j < table->commands[i]->args_num; j++)
				dprintf(2, " %s", table->commands[i]->cmd_args[j]);
			dprintf(2, "\n");
		}
		else
			dprintf(2, "\tsimple cmd is NULL\n");
	}
}

__attribute__((weak)) void	_DEBUG_print_hashtable(t_hashtable *ht)
{
	t_pair	*pair;
	int		i;

	i = -1;
	dprintf(2, "HASHTABLE: size=%d, count=%d, load_ratio=%.3f\n", ht->size, ht->count, (float)ht->count / ht->size);
	while (++i < ht->size)
	{
		pair = ht->table[i];
		dprintf(2, "table[%d]", i);
		while (pair)
		{
			dprintf(2, " -> (%s; %s)", pair->key, pair->value);
			pair = pair->next;
		}
		dprintf(2, "\n");
	}
	dprintf(2, "\n");
}

__attribute__((weak)) void	_DEBUG_print_cmd_blocks(t_cmd_block *cmd_blocks)
{
	dprintf(2, "<------------- DEBUG PRINT CMD BLOCKS ------------->\n");
	if (!cmd_blocks)
	{
		dprintf(2, "cmd blocks is NULL\n");
		return ;
	}
	int j = 0;
	do
	{
		dprintf(2, "delimiter: %d\n", cmd_blocks[j].delimiter);
		dprintf(2, "\t<====== DEBUG PRINT CMD TABLE ======>\n");
		if (!cmd_blocks[j].table)
		{
			dprintf(2, "\ttable is NULL\n");
			return ;
		}
		dprintf(2, "\tis_append: %d | stdin file:  %s\n", cmd_blocks[j].table->redirect.is_stdin_append, cmd_blocks[j].table->redirect._stdin);
		dprintf(2, "\tis_append: %d | stdout file: %s\n", cmd_blocks[j].table->redirect.is_stdout_append, cmd_blocks[j].table->redirect._stdout);
		dprintf(2, "\tcommands: %d\n", cmd_blocks[j].table->commands_num);
		for (int i = 0; i < cmd_blocks[j].table->commands_num; i++)
		{
			dprintf(2, "\t\t<== SIMPLE COMMAND ==>\n");
			if (cmd_blocks[j].table->commands[i])
			{
				dprintf(2, "\t\tbinary: %s\n", cmd_blocks[j].table->commands[i]->cmd);
				dprintf(2, "\t\ttype: %s\n", _DEBUG_cmd_type_to_str(cmd_blocks[j].table->commands[i]->type));
				dprintf(2, "\t\targs (%d):", cmd_blocks[j].table->commands[i]->args_num);
				for (int k = 0; k < cmd_blocks[j].table->commands[i]->args_num; k++)
					dprintf(2, " %s", cmd_blocks[j].table->commands[i]->cmd_args[k]);
				dprintf(2, "\n");
			}
			else
				dprintf(2, "\t\tsimple cmd is NULL\n");
		}
	} while (cmd_blocks[j++].delimiter != CMDBL_END);
}

#endif
