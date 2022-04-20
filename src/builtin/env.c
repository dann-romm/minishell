/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:01:54 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/21 00:32:40 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "hashtable.h"

static void	print_hashtable(t_hashtable *ht)
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

int	ft_env(void)
{
	print_hashtable(g_shell->env_global);
	return (0);
}
