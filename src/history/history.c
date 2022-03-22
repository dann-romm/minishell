#include "shell.h"

void	save_history(char *str)
{
	if (str)
		add_history((const char *)str);
}
