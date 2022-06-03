/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:25:31 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/22 20:36:53 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# define LOAD_RATIO_LIMIT 0.75

# include <stdlib.h>
# include <errno.h>

typedef struct s_pair
{
	char			*key;
	char			*value;
	struct s_pair	*next;
}	t_pair;

typedef struct s_hashtable
{
	t_pair			**table;
	uint32_t		size;
	uint32_t		count;
	unsigned int	(*hash)(char *key, uint32_t size);
}	t_hashtable;

// hash.c
uint32_t	djb2_hash(char *key, uint32_t size);

// pair.c
t_pair		*init_pair(char *key, char *value);
int			push_front_pair(t_pair **head, t_pair *pair);
int			remove_pair(t_pair **head, char *key);
t_pair		*find_pair(t_pair *head, char *key);

// hashtable.c
t_hashtable	*init_hashtable(uint32_t size);
int32_t		remove_hashtable(t_hashtable *ht, char *key);
char		*find_hashtable(t_hashtable *ht, char *key);
void		clear_hashtable(t_hashtable *ht);
void		delete_hashtable(t_hashtable **ht);

// insert_hashtable.c
int32_t		insert_hashtable(t_hashtable *ht, char *key, char *value);

// hashtable_to_sorted_array.c
char		**hashtable_to_sorted_array(t_hashtable *ht);

#endif
