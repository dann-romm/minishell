#include "hashtable.h"

int32_t	length_hashtable(t_hashtable *ht)
{
	int		i;
	int		len;
	t_pair	*pair;

	len = 0;
	i = -1;
	while (++i < ht->size)
	{
		pair = ht->table[i];
		while (pair)
		{
			len++;
			pair = pair->next;
		}
	}
	return (len);
}
