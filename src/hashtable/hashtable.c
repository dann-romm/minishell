#include "hashtable.h"
#include "libft_funcs.h"
#include "executor.h"

t_hashtable	*init_hashtable(uint32_t size)
{
	t_hashtable	*ht;

	ht = malloc(sizeof(t_hashtable));
	if (!ht)
	{
		errno = ENOMEM;
		return (NULL);
	}
	ht->hash = djb2_hash;
	ht->count = 0;
	ht->size = size;
	ht->table = malloc(sizeof(t_pair *) * ht->size);
	if (!ht->table)
	{
		errno = ENOMEM;
		free(ht);
		return (NULL);
	}
	while (size)
		ht->table[--size] = NULL;
	return (ht);
}

int partition(char **str, int l, int r)
{
	char	*mid = str[(l + r) / 2];
	int		i = l;
	int		j = r;
	char	*tmp;
	while (i <= j) 
	{
		while (ft_strcmp(str[i], mid) < 0)
			i++;
		while (ft_strcmp(str[j], mid) > 0)
			j--;
		if (i > j)
			break;
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
	}
	return j;
}

void quick_sort(char **str, int l, int r)
{
	int diff = 0;
	if (l < r)
	{
		diff = partition(str, l, r);
		quick_sort(str, l, diff);
		quick_sort(str, diff + 1, r);
	}
}

char	**sort_hashtable(t_hashtable *ht)
{
	char **tmp = ht_to_array(ht);
	int strlen = 0, i = 3;
	while (tmp[strlen])
		strlen++;
	quick_sort(tmp, i, strlen - 1);
	return (tmp);
}

int32_t	insert_hashtable(t_hashtable *ht, char *key, char *value)
{
	uint32_t	index;
	t_pair		*pair;

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

#include <stdio.h>

uint32_t	rehashing(t_hashtable *ht)
{
	int32_t		i;
	t_pair		*pair;
	t_pair		*next;
	t_pair		**new_table;
	uint32_t	new_index;
	uint32_t	new_count;

	new_table = malloc(sizeof(t_pair *) * (ht->size << 1));
	i = -1;
	while (++i < (ht->size << 1))
		new_table[i] = NULL;
	new_count = 0;
	i = -1;
	while (++i < ht->size)
	{
		pair = ht->table[i];
		while (pair)
		{
			next = pair->next;
			new_index = ht->hash(pair->key, (ht->size << 1));
			if (!new_table[new_index])
				new_count++;
			if (push_front_pair(&(new_table[new_index]), pair))
			{
				free(new_table);
				return (1);
			}
			pair = next;
		}
	}
	free(ht->table);
	ht->table = new_table;
	ht->count = new_count;
	ht->size <<= 1;
	return (0);
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
