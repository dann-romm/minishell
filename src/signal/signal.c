#include "shell.h"

void	signal_handler(int signum)
{
	if (signum == SIGINT) // если пользователь нажал клавишу CTRL-C, на экран выводится пустая строка
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		// rl_redisplay();
	}
	else if (signum == SIGTERM)
	{
		write(1, "exit\n", 5);
		exit(1);
	}
}

void	setting_signal() //  signal() дает указание Borland С++ выполнить функцию, переданную вторым параметром, в случае получения сигнала 
{
	signal(SIGINT, signal_handler);  // CTRL + C - завершение процесса
	signal(SIGTERM, signal_handler); // CTRL + D - завершение всей программы
	// signal(SIGQUIT, signal_handler); // CTRL + / - this signal must be ignored
}
