/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:13:36 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/21 18:41:55 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gshell.h"
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
	while (++i < (int) ht->size)
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
	while (++i < (int) ht->size)
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

char	*three_str_cat(char *s1, char *s2, char *s3)
{
	int		len;
	int		i;
	int		j;
	char	*dest;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	while (s1[i] && i < (len + 1))
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] && i < (len + 1))
		dest[i++] = s2[j++];
	j = 0;
	while (s3[j] && i < (len + 1))
		dest[i++] = s3[j++];
	dest[i] = '\0';
	return (dest);
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

void	delete_shell(void)
{
	delete_hashtable(&(g_shell.env_global));
	delete_hashtable(&(g_shell.env_local));
	delete_cmd_blocks(&(g_shell.cmd_blocks));
	delete_token_list(&(g_shell.list));
}
