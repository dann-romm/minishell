/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:13:20 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/20 23:47:42 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft_funcs.h"

char	*ft_strndup(char *str, size_t length)
{
	char	*p;
	int		i;

	i = ft_strlen(str);
	p = (char *)malloc(sizeof(char) * (i + 1));
	if (!p)
		return (NULL);
	i = -1;
	while (str[++i] && i < length)
		p[i] = str[i];
	p[i] = '\0';
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char) c)
		s++;
	if (*s == (char) c)
		return ((char *) s);
	return (0);
}

int32_t	int32_abs(int32_t n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

int	is_str_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		tmp;

	tmp = n;
	len = (n <= 0);
	while (tmp != 0)
	{
		len++;
		tmp /= 10;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len--] = '\0';
	str[0] = '-';
	if (n == 0)
		str[0] = '0';
	n = int32_abs(n);
	while (n > 0)
	{
		str[len--] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}
