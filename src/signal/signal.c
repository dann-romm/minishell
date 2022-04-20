/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:57:42 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/21 00:26:33 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		write(1, "exit\n", 5);
		exit(1);
	}
}

void	heredoc_signal_handler(int signum)
{
	(void) signum;
	write(1, "\n", 1);
	exit(1);
}

void	setting_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}
