#include "shell.h"
#include <history.h>

void	signal_handler(int signum)
{
	if (signum == SIGINT) // если пользователь нажал клавишу CTRL-C, на экран выводится пустая строка
	{
		rl_on_new_line();
		rl_replace_line("", 1); // Удаляет строку, которая уже попала в очередь
		rl_redisplay();
	}
	// else
	// when we caught SIGTERM or SIGQUIT we use kill() (maybe. try it) 
}

void	setting_signal() //  signal() дает указание Borland С++ выполнить функцию, переданную вторым параметром, в случае получения сигнала signal
{
	signal(SIGINT, signal_handler);  // CTRL + C - завершение процесса
	signal(SIGTERM, signal_handler); // CTRL + D - 
	signal(SIGQUIT, signal_handler); // CTRL + / - завершение программы
}
