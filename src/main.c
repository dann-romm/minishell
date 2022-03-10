#include "shell.h"
#include "hashtable.h"
#include "libft_funcs.h"

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

	t_hashtable *ht = init_hashtable(1);
	insert_hashtable(ht, "PWD", "/Users/zaira/Desktop");
	print_hashtable(ht);
	insert_hashtable(ht, "OLDPWD", "/Users/zaira");
	print_hashtable(ht);
	insert_hashtable(ht, "HOME", "/Users/zaira");
	print_hashtable(ht);

	_DEBUG_assert_right_hashtable(ht);

	// insert_hashtable(ht, "NUMBER_3", "3");
	// insert_hashtable(ht, "NUMBER_4", "4");
	// insert_hashtable(ht, "NUMBER_5", "5");
	// insert_hashtable(ht, "NUMBER_5!!", "120!");
	// print_hashtable(ht);
	// insert_hashtable(ht, "PATH", "/second/path");
	// insert_hashtable(ht, "PATH", "/new/path");
	// printf("found value = %s\n", find_hashtable(ht, "NUMBER_2"));
	// printf("found value = %s\n", find_hashtable(ht, "NUMBER_3"));
	// remove_hashtable(ht, "NUMBER_2");
	// remove_hashtable(ht, "NUMBER_3");
	// print_hashtable(ht);

	delete_hashtable(&ht);
}
