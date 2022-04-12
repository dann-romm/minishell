#include "shell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT) // если пользователь нажал клавишу CTRL-C, на экран выводится пустая строка
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_clear_visible_line();
		rl_redisplay();
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

void	setting_signal() //  signal() дает указание Borland С++ выполнить функцию, переданную вторым параметром, в случае получения сигнала 
{
	signal(SIGINT, signal_handler);  // CTRL + C - завершение процесса
	signal(SIGTERM, signal_handler); // CTRL + D - завершение всей программы
	signal(SIGQUIT, SIG_IGN); // CTRL + / - this signal must be ignored
}
