#include "libft_funcs.h"

void free_split(char **pointers)
{
	int i = 0;
	while (pointers[i])
	{
		free(pointers[i]);
		i++;
	}
	free(pointers);
}
