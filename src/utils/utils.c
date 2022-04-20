/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgwyness <mgwyness@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:13:36 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/20 23:30:34 by mgwyness         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"

char	**adapt_cmd_args(t_simple_cmd *command)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	j = 0;
	new = (char **)malloc(sizeof(char *) * (command->args_num + 2));
	if (new == 0)
		return (0);
	new[i] = ft_strdup(command->cmd);
	i++;
	while (i <= command->args_num)
	{
		new[i] = ft_strdup(command->cmd_args[j]);
		i++;
		j++;
	}
	new[i] = 0;
	return (new);
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

char	**ht_to_array(t_hashtable *ht)
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

char	*find_path(t_simple_cmd *command)
{
	int		i;
	int		all;
	char	*cur_dir;
	char	**paths;

	cur_dir = find_hashtable(g_shell->env_global, "PWD");
	cur_dir = three_str_cat(cur_dir, "/", command->cmd);
	if (!access(cur_dir, F_OK))
		return (cur_dir);
	free(cur_dir);
	paths = ft_split(find_hashtable(g_shell->env_global, "PATH"), ':');
	i = -1;
	while (paths[++i])
	{
		cur_dir = three_str_cat(paths[i], "/", command->cmd);
		if (!access(cur_dir, F_OK))
		{
			free_2d_array(paths);
			return (cur_dir);
		}
		free(cur_dir);
	}
	free_2d_array(paths);
	printf("minishell: %s: command not found\n", command->cmd);
	return (0);
}

//A  word  consisting  only  of alphanumeric characters and under‐
//scores, and beginning with an alphabetic character or an  under‐
//score.  Also referred to as an identifier.
// 1 - невалидно
// 0 - валидно
int	check_input(char *str)
{
	if (!is_alpha(*str) && *str != '_')
		return (1);
	while (*(++str))
	{
		if (!is_alnum(*str) && *str != '_')
			return (1);
	}
	return (0);
}
