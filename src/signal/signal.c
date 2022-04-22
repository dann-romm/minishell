/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:57:42 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/22 20:30:49 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gshell.h"
#include "shell.h"
#include "parser.h"
#include "lexer.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_clear_visible_line();
		signal(SIGINT, signal_handler);
	}
	else if (signum == SIGTERM)
	{
		delete_shell();
		write(1, "exit\n", 5);
		exit(1);
	}
}

void	heredoc_signal_handler(int signum)
{
	(void) signum;
	delete_shell();
	write(1, "\n", 1);
	exit(1);
}

void	setting_signal(void)
{
	signal(SIGTERM, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
