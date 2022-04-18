#include "shell.h"
#include "lexer.h"
#include "libft_funcs.h"

t_source	*init_source(char *str)
{
	t_source	*source;

	source = (t_source *)malloc(sizeof(t_source));
	if (!source)
		return (NULL);
	source->pos = -1;
	source->bufsize = ft_strlen(str);
	source->buffer = ft_strdup(str);
	if (!source->buffer)
	{
		free(source);
		return (NULL);
	}
	source->strsize = 10;
	source->strlen = 0;
	source->str = (char *)malloc(sizeof(char) * 10);
	if (!source->str)
	{
		free(source->buffer);
		free(source);
		return (NULL);
	}
	source->str[0] = '\0';
	return (source);
}

void	reallocate_str(t_source *src)
{
	char	*tmp;

	if (!src || !src->str)
	{
		errno = ENODATA;
		return ;
	}
	src->strsize *= 2;
	tmp = (char *)malloc(sizeof(char) * (src->strsize + 1));
	if (!tmp)
		return ;
	src->str[src->strlen] = '\0';
	ft_strcpy(tmp, src->str);
	free(src->str);
	src->str = tmp;
}

void	skip_whitespaces(t_source *src)
{
	char	c;

	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return ;
	}
	c = peek(src);
	while (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
	{
		next_char(src);
		c = peek(src);
	}
}

void	clear_str(t_source *src)
{
	src->strlen = 0;
	src->str[0] = '\0';
}

void	delete_source(t_source **src)
{
	if (!src)
		return ;
	if (*src)
	{
		if ((*src)->buffer)
			free((*src)->buffer);
		if ((*src)->str)
			free((*src)->str);
		free(*src);
		*src = NULL;
	}
}
