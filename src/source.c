#include "shell.h"

char	peek(t_source *src)
{
	if (!src || !src->buffer)
	{
		errno = ENODATA;
		return (ERRCHAR);
	}
	if (src->pos + 1 >= src->bufsize)
		return (EOFCHAR);
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
		return (EOFCHAR);
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
		return (EOFCHAR);
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
