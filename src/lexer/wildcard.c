/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:01:10 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/20 22:01:11 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft_funcs.h"
#include "shell.h"

static int	find_substr(char *str, char *substr)
{
	int	i;
	int	len;

	if (!str || !substr)
		return (-1);
	if (!(*substr))
		return (0);
	len = ft_strlen(substr);
	i = 0;
	while (*str)
	{
		if (!ft_strncmp(str, substr, len))
			return (i);
		str++;
		i++;
	}
	return (-1);
}

static int	is_head_matched(char **pattern, struct dirent *file, t_source *src)
{
	int	index;

	while (**pattern && **pattern != '*')
	{
		save_char(src, **pattern);
		(*pattern)++;
	}
	if (**pattern)
		(*pattern)++;
	if (!ft_strncmp(src->str, file->d_name, src->strlen))
		index = src->strlen;
	else
		index = -1;
	clear_str(src);
	if (index == -1)
		return (0);
	ft_memmove(file->d_name, file->d_name + index, file->d_namlen);
	file->d_namlen -= index;
	return (1);
}

static int	is_tail_matched(char *pattern, struct dirent *file, t_source *src)
{
	int	index;

	while (*pattern)
	{
		save_char(src, *pattern);
		if (*pattern == '*')
			clear_str(src);
		pattern++;
	}
	if (!ft_strncmp(src->str,
			&(file->d_name[file->d_namlen - src->strlen]), src->strlen))
		index = src->strlen;
	else
		index = -1;
	clear_str(src);
	if (index == -1)
		return (0);
	file->d_name[file->d_namlen - index] = '\0';
	file->d_namlen -= index;
	return (1);
}

static int	is_pattern_matched(char *pattern,
	struct dirent *file, t_source *src)
{
	int	index;

	if (!is_head_matched(&pattern, file, src)
		|| !is_tail_matched(pattern, file, src))
		return (0);
	while (*pattern)
	{
		if (*pattern == '*')
		{
			index = find_substr(file->d_name, src->str);
			if (index == -1)
			{
				clear_str(src);
				return (0);
			}
			clear_str(src);
			ft_memmove(file->d_name,
				file->d_name + index + src->strlen, file->d_namlen);
		}
		else
			save_char(src, *pattern);
		pattern++;
	}
	return (1);
}

void	handle_wildcard(t_source *src, t_token **token)
{
	char			*pattern;
	DIR				*dir;
	struct dirent	*file;
	char			*filename;

	pattern = ft_strdup(src->str);
	clear_str(src);
	dir = opendir(find_hashtable(g_shell->env_global, "PWD"));
	if (!dir)
	{
		free(pattern);
		return ((void)error_manager(ERRT_PWD_ERR, 0, 0));
	}
	file = readdir(dir);
	while (file)
	{
		filename = ft_strdup(file->d_name);
		if (is_pattern_matched(pattern, file, src))
			push_back_token_list(token, init_token(T_ID, filename));
		free(filename);
		file = readdir(dir);
	}
	if (!(*token))
		*token = init_token(T_ID, pattern);
	free(pattern);
}
