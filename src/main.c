#include "shell.h"
#include "lexer.h"
#include "hashtable.h"
#include "libft_funcs.h"
#include "parser.h"
#include "executor.h"
#include "prompt.h"
#include "signals.h"
// #include "debug.h"

void	update_shlvl(void)
{
	char	*shlvl;

	shlvl = find_hashtable(g_shell->env_global, "SHLVL");
	if (!shlvl)
	{
		errno = 1;
		return ;
	}
	shlvl = ft_itoa(ft_atoi(shlvl) + 1);
	insert_hashtable(g_shell->env_global, "SHLVL", shlvl);
}

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
	update_shlvl();
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
		list = lexer(input);
		signal(SIGINT, SIG_IGN);
		cmd_block = parser(&list);
		if (!cmd_block)
			g_shell->exit_status = errno;
		else
			g_shell->exit_status = execute(cmd_block);
		delete_token_list(&list);
		free(input);
	}
}
