/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 02:30:16 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/21 02:30:17 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
