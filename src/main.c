#include "shell.h"
#include "lexer.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "builtin.h"
#include "parser.h"
#include "executor.h"
#include "prompt.h"
#include "signals.h"
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
	fill_hashtable(env);
	insert_hashtable(g_shell->env_global, "PS1", "minishell > ");
	insert_hashtable(g_shell->env_global, "PS2", "> ");
	g_shell->exit_status = 0;
}

void	test(t_hashtable *ht, uint32_t size)
{
	ht->hash = djb2_hash;
	ht->count = 0;
	ht->size = size;
	ht->table = malloc(sizeof(t_pair *) * ht->size);
	while (size)
		ht->table[--size] = NULL;
}


int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_token			*list;
	t_cmd_block		*cmd_block;

	init_shell(env);

	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGTERM, signal_handler);
		input = prompt1();
		add_history(input);
		list = create_token_list(input);

		// _DEBUG_print_token_list(list);
		cmd_block = parser(&list);
		if (!cmd_block)
			g_shell->exit_status = errno;

		signal(SIGINT, SIG_IGN);
		g_shell->exit_status = execute(cmd_block);

		delete_token_list(&list);
		free(input);
	}
}
