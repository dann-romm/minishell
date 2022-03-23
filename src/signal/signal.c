#include "shell.h"

// лишнее, потому что эти хедеры уже подключены из shell.h
// #include <signal.h> 
// #include <readline/readline.h>

void	signal_handler(int signum)
{
	if (signum == SIGINT) // если пользователь нажал клавишу CTRL-C, на экран выводится пустая строка
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1); // 1 - выводит новый промпт, 0 - удаляет из очереди промпт
		rl_redisplay();
	}
	// else
	// when we caught SIGTERM or SIGQUIT we use kill() (maybe. try it) 
}

void	setting_signal() //  signal() дает указание Borland С++ выполнить функцию, переданную вторым параметром, в случае получения сигнала 
{
	signal(SIGINT, signal_handler);  // CTRL + C - завершение процесса
	// signal(SIGTERM, signal_handler); // CTRL + D - завершение всей программы
	// signal(SIGQUIT, signal_handler); // CTRL + / - this signal must be ignored
}
