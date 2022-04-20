/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 23:13:26 by mgwyness          #+#    #+#             */
/*   Updated: 2022/04/21 02:26:08 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_funcs.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (*s1 == *s2) && *s1)
	{
		s1++;
		s2++;
		i++;
	}
	if (i != n)
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
	else
		return (0);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s && *s != (char) c)
		s++;
	if (*s == (char) c)
		return ((char *) s);
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	ans;

	i = 0;
	ans = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = (str[i] == '-') * (-1) + (str[i] == '+');
		i++;
	}
	while (str[i] == '0')
		i++;
	if (str[i] > '0' && str[i] <= '9')
		ans = sign * (str[i++] - '0');
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((ans * 10 + sign * (str[i] - '0') > 0) != (ans > 0))
			return (0);
		ans = ans * 10 + sign * (str[i] - '0');
		i++;
	}
	return (ans);
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
