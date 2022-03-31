#include "lexer.h"
#include "libft_funcs.h"
#include "shell.h"

int	find_substr(char *str, char *substr) // протестировать работу функции
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

int find_head_matching(char *pattern, struct dirent *file, t_source *src)
{
	while (*pattern && *pattern != '*')
		save_char(src, *pattern++);
	if (*pattern)
		pattern++;

	if (!ft_strncmp(src->str, file->d_name, src->strlen))
		return (src->strlen);
	return (-1);
}

int find_tail_matching(char *pattern, struct dirent *file, t_source *src)
{
	while (*pattern)
	{
		save_char(src, *pattern);
		if (*pattern == '*')
			clear_str(src);
		pattern++;
	}
	if (!ft_strncmp(src->str, &(file->d_name[file->d_namlen - src->strlen]), src->strlen))
		return (src->strlen);
	return (-1);
}

// sca*ne*.h

int	is_pattern_matched(char *pattern, struct dirent *file, t_source *src)
{
	int	index;

	printf("filename: %s\n", file->d_name);

	index = find_head_matching(pattern, file, src);
	clear_str(src);
	if (index == -1)
		return (0);
	ft_memmove(file->d_name, file->d_name + index, file->d_namlen);
	pattern += index + 1;
	file->d_namlen -= index;


	index = find_tail_matching(pattern, file, src);
	clear_str(src);
	if (index == -1)
		return (0);
	file->d_name[file->d_namlen - index] = '\0';
	file->d_namlen -= index;

	// while (*pattern)
	// {
	// 	if (*pattern == '*')
	// 	{
			
	// 	}
	// 	save_char(src, *pattern);
	// 	pattern++;
	// }

	printf("filename : %s\n", file->d_name);
	printf("pattern: (%s)\n", pattern);

	printf("________________\n");
	return (0);
}

t_token	*handle_wildcard(t_source *src, t_token *token)
{
	char			*pattern;
	DIR				*dir;
	struct dirent	*file;

	pattern = ft_strdup(src->str);
	clear_str(src);

	dir = opendir(getcwd(0, 0));
	if (!dir)
	{
		// error
		return (0);
	}
	
	file = readdir(dir);
	while (file)
	{
		if (is_pattern_matched(pattern, file, src))
		{
			return (0);
		}
		file = readdir(dir);
	}
	token->value = ft_strdup(src->str);
	clear_str(src);
	return (token);
}
