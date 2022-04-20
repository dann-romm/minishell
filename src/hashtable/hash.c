/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 02:30:21 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/21 02:30:22 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	djb2_hash(char *key, unsigned int size)
{
	unsigned int	hash;
	int				i;

	hash = 5381;
	i = -1;
	while (key[++i])
		hash = (hash << 5) + hash + (unsigned int)key[i];
	return (hash % size);
}
