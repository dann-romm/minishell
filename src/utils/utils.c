/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:13:36 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/21 02:46:02 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"

char	**hashtable_to_array(t_hashtable *ht)
{
	int		i;
	int		j;
	char	**env_array;
	t_pair	*pair;

	i = -1;
	j = 0;
	env_array = (char **)malloc(sizeof(char *) * (length_hashtable(ht) + 1));
	while (++i < ht->size)
	{
		pair = ht->table[i];
		while (pair)
		{
			env_array[j] = three_str_cat(pair->key, "=", pair->value);
			j++;
			pair = pair->next;
		}
	}
	env_array[j] = 0;
	return (env_array);
}

int	length_hashtable(t_hashtable *ht)
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

// A  word  consisting  only  of alphanumeric characters and under‐
// scores, and beginning with an alphabetic character or an  under‐
// score.  Also referred to as an identifier.
// 1 - invalid
// 0 - valid
int	is_variable_valid(char *str)
{
	if (!is_alpha(*str) && *str != '_')
		return (0);
	while (*(++str))
	{
		if (!is_alnum(*str) && *str != '_')
			return (0);
	}
	return (1);
}
