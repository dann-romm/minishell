#include "shell.h"
#include "hashtable.h"

void ft_pwd(t_hashtable *ht)
{
	char *cur_dir;
	cur_dir = (char *)malloc(sizeof(char) * 999);
	cur_dir = getcwd(cur_dir, 999);
	if (!cur_dir)
		return ;
	printf("%s\n", cur_dir);
	free(cur_dir);
}
