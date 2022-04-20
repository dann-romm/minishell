#include "hashtable.h"
#include "libft_funcs.h"

static uint32_t	rehashing(t_hashtable *ht)
{
	t_hashtable	*new_ht;
	t_pair		*pair;
	t_pair		*next;

	new_ht = init_hashtable(ht->size * 2);
	if (!new_ht)
		return (1);
	ht->count = 0;
	while (ht->size--)
	{
		pair = ht->table[ht->size];
		while (pair)
		{
			next = pair->next;
			if (!new_ht->table[ht->hash(pair->key, new_ht->size)])
				ht->count++;
			push_front_pair(&(new_ht->table[ht->hash(pair->key,
						new_ht->size)]), pair);
			pair = next;
		}
	}
	free(ht->table);
	ht->table = new_ht->table;
	ht->size = new_ht->size;
	free(new_ht);
	return (0);
}

int32_t	insert_hashtable(t_hashtable *ht, char *key, char *value)
{
	uint32_t	index;
	t_pair		*pair;

	if (!value)
		return (1);
	index = ht->hash(key, ht->size);
	pair = find_pair(ht->table[index], key);
	if (pair)
	{
		free(pair->value);
		pair->value = ft_strdup(value);
		if (!pair->value)
			return (1);
		return (0);
	}
	if (!ht->table[index])
		ht->count++;
	if (push_front_pair(&(ht->table[index]), init_pair(key, value)))
		return (1);
	if ((float)ht->count / ht->size >= LOAD_RATIO_LIMIT)
		rehashing(ht);
	return (0);
}
