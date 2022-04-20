/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 22:01:00 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/20 22:01:01 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "lexer.h"
#include "libft_funcs.h"

char	peek(t_source *src)
{
	if (!src || !src->buffer)
		return (ERRCHAR);
	if (src->pos + 1 >= src->bufsize)
		return (EOF);
	return (src->buffer[src->pos + 1]);
}

char	peek2(t_source *src)
{
	if (!src || !src->buffer)
		return (ERRCHAR);
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

int	unget_char(t_source *src)
{
	if (src->pos < 0)
		return (1);
	src->pos--;
	return (0);
}

int	save_char(t_source *src, char c)
{
	if (!src || !src->str)
	{
		errno = ENODATA;
		return (1);
	}
	src->str[src->strlen++] = c;
	if (src->strlen == src->strsize)
		reallocate_str(src);
	src->str[src->strlen] = '\0';
	return (0);
}
