#include "shell.h"
#include "hashtable.h"

int ft_pwd()
{
	char *cur_dir;
	cur_dir = (char *)malloc(sizeof(char) * 999);
	if (!cur_dir)
		return (1);
	cur_dir = getcwd(cur_dir, 999);
	printf("%s\n", cur_dir);
	free(cur_dir);
	return (0);
}

