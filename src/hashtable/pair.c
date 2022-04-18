#include "hashtable.h"
#include "libft_funcs.h"

t_pair	*init_pair(char *key, char *value)
{
	t_pair	*pair;

	pair = malloc(sizeof(t_pair));
	if (!pair)
		return (NULL);
	pair->key = ft_strdup(key);
	if (!pair->key)
	{
		free(pair);
		return (NULL);
	}
	pair->value = ft_strdup(value);
	if (!pair)
	{
		free(pair->key);
		free(pair);
		return (NULL);
	}
	pair->next = NULL;
	return (pair);
}

int	push_front_pair(t_pair **head, t_pair *pair)
{
	if (!head | !pair)
		return (1);
	pair->next = *head;
	*head = pair;
	return (0);
}

int	remove_pair(t_pair **head, char *key)
{
	t_pair	*tmp;
	t_pair	*prev;

	if (!head || !(*head))
		return (1);
	tmp = *head;
	while (tmp && ft_strcmp(tmp->key, key))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		free(tmp->key);
		free(tmp->value);
		if (tmp == *head)
			*head = tmp->next;
		else
			prev->next = tmp->next;
		free(tmp);
		return (0);
	}
	return (1);
}

t_pair	*find_pair(t_pair *head, char *key)
{
	t_pair	*tmp;

	if (!key)
		return (NULL);
	tmp = head;
	while (tmp && ft_strcmp(tmp->key, key))
		tmp = tmp->next;
	return (tmp);
}
