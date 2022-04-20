#include "hashtable.h"
#include "libft_funcs.h"
#include "executor.h"

t_hashtable	*init_hashtable(uint32_t size)
{
	t_hashtable	*ht;

	ht = (t_hashtable *)malloc(sizeof(t_hashtable));
	if (!ht)
		return (NULL);
	ht->hash = djb2_hash;
	ht->count = 0;
	ht->size = size;
	ht->table = malloc(sizeof(t_pair *) * ht->size);
	if (!ht->table)
	{
		free(ht);
		return (NULL);
	}
	ft_memset(ht->table, 0, sizeof(t_pair *) * ht->size);
	return (ht);
}

uint32_t	rehashing(t_hashtable *ht)
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

int32_t	remove_hashtable(t_hashtable *ht, char *key)
{
	uint32_t	index;

	index = ht->hash(key, ht->size);
	if (!remove_pair(&(ht->table[index]), key))
	{
		if (!ht->table[index])
			ht->count--;
		return (0);
	}
	return (1);
}

// warning, this function doesn't copy vaule,
// but give a pointer to the value stored in hashtable
char	*find_hashtable(t_hashtable *ht, char *key)
{
	uint32_t	index;
	t_pair		*pair;

	index = ht->hash(key, ht->size);
	pair = find_pair(ht->table[index], key);
	if (!pair)
		return (NULL);
	return (pair->value);
}

void	clear_hashtable(t_hashtable *ht)
{
	int32_t	i;

	i = -1;
	while (++i < ht->size)
	{
		while (ht->table[i])
			remove_pair(&(ht->table[i]), ht->table[i]->key);
	}
	ht->count = 0;
}

void	delete_hashtable(t_hashtable **ht)
{
	if (!ht)
		return ;
	clear_hashtable(*ht);
	free((*ht)->table);
	free(*ht);
	*ht = NULL;
}

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

void	print_hashtable(t_hashtable *ht)
{
	t_pair	*pair;
	int		i;

	i = -1;
	while (++i < ht->size)
	{
		pair = ht->table[i];
		while (pair)
		{
			printf("%s=%s\n", pair->key, pair->value);
			pair = pair->next;
		}
	}
}
