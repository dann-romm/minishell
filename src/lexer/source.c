#include "lexer.h"
#include "libft_funcs.h"
#include "shell.h"

t_source	*init_source(char *str)
{
	t_source	*source;

	source = (t_source *)malloc(sizeof(t_source));
	if (!source)
	{
		errno = ENOMEM;
		return (NULL);
	}
	source->pos = -1;
	source->bufsize = ft_strlen(str);
	source->buffer = ft_strdup(str);
	if (!source->buffer)
	{
		errno = ENOMEM;
		free(source);
		return (NULL);
	}
	source->strsize = 10;
	source->strlen = 0;
	source->str = (char *)malloc(sizeof(char) * 10);
	if (!source->str)
	{
		errno = ENOMEM;
		free(source->buffer);
		free(source);
		return (NULL);
	}
	source->str[0] = '\0';
	return (source);
}

char	peek(t_source *src)
{
	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}
	if (src->pos + 1 >= src->bufsize)
		return (EOF);
	return (src->buffer[src->pos + 1]);
}

char	peek2(t_source *src)
{
	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}
	if (src->pos + 2 >= src->bufsize)
		return (EOF);
	return (src->buffer[src->pos + 2]);
}

char	next_char(t_source *src)
{
	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}
	if (++src->pos >= src->bufsize)
	{
		src->pos = src->bufsize;
		return (EOF);
	}
	return (src->buffer[src->pos]);
}

void	unget_char(t_source *src)
{
	if (src->pos < 0)
		return ;
	src->pos--;
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
	while (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
	{
		next_char(src);
		c = peek(src);
	}
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
	tmp = (char *)malloc(sizeof(char) * src->strsize);
	if (!tmp)
	{
		errno = ENOMEM;
		return ;
	}
	ft_strcpy(tmp, src->str);
	free(src->str);
	src->str = tmp;
}

void	save_char(t_source *src, char c) // segfault bug
{
	if (!src || !src->str)
	{
		errno = ENODATA;
		return ;
	}
	src->str[src->strlen++] = c;
	if (src->strlen == src->strsize)
		reallocate_str(src);
	src->str[src->strlen] = '\0';
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
