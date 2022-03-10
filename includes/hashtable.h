#ifndef HASHTABLE_H
# define HASHTABLE_H

# define LOAD_RATIO_LIMIT 0.75

# include <stdlib.h>
# include <errno.h>
# include <string.h> // remove and write own memset()

typedef struct s_pair
{
	char			*key;
	char			*value;
	struct s_pair	*next;
}	t_pair;

typedef struct s_hashtable
{
	t_pair		**table;
	uint32_t	size;
	uint32_t	count;
	uint32_t	(*hash)(char *key, uint32_t size);
}	t_hashtable;

void		fill_ht(char **env);
void		print_ht(t_hashtable *ht);

t_pair		*init_pair(char *key, char *value);
int			push_front(t_pair **head, t_pair *pair);
int			remove_pair(t_pair **head, char *key);
t_pair		*find_pair(t_pair *head, char *key);

t_hashtable	*init_hashtable(uint32_t size);
int32_t		insert_hashtable(t_hashtable *ht, char *key, char *value);
int32_t		remove_hashtable(t_hashtable *ht, char *key);
char		*find_hashtable(t_hashtable *ht, char *key);
void		clear_hashtable(t_hashtable *ht);
void		delete_hashtable(t_hashtable **ht);

uint32_t	djb2_hash(char *key, uint32_t size);
uint32_t	rehashing(t_hashtable *ht);

void		print_hashtable(t_hashtable *ht); // for debugging

// t_hashtable	*fill_with_env(char **env); // TODO

#endif