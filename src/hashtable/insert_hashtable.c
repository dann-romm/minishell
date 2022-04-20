/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 02:30:10 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/21 02:33:44 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "libft_funcs.h"

static uint32_t	rehashing(t_hashtable *ht)
{
	t_hashtable	*_ht;
	t_pair		*cur;
	t_pair		*next;

	_ht = init_hashtable(ht->size * 2);
	if (!_ht)
		return (1);
	ht->count = 0;
	while (ht->size--)
	{
		cur = ht->table[ht->size];
		while (cur)
		{
			next = cur->next;
			if (!_ht->table[ht->hash(cur->key, _ht->size)])
				ht->count++;
			push_front_pair(&(_ht->table[ht->hash(cur->key, _ht->size)]), cur);
			cur = next;
		}
	}
	free(ht->table);
	ht->table = _ht->table;
	ht->size = _ht->size;
	free(_ht);
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
