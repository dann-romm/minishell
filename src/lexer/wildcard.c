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
	return (0);
}

int	is_pattern_matched(char *pattern, struct dirent *file, t_source *src)
{
	int	i;

	while (*pattern != '*')
		save_char(src, *pattern++);
	pattern++;

	i = 0;
	while (src->str[i])
	{
		if (src->str[i] != file->d_name[i])
		{
			clear_str(src);
			return (0);
		}
		i++;
	}
	printf("first part: (%s)\n", src->str);
	clear_str(src);
	printf("pattern after first look: (%s)\n", pattern);

	// find_substr для всех серединных частей

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
