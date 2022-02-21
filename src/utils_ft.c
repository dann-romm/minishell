#include <stdlib.h>

int	is_alnum(char c)
{
	return ((c >= '0' && c <= '9')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'));
}

int	is_space(char c)
{
	return (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (*str++)
		i++;
	return (i);
}

char	*ft_strcat(char *dst, char *src)
{
	int	i;
	int	len;

	i = 0;
	while (dst[i] != '\0')
		i++;
	len = i;
	i = -1;
	while (src[++i] != '\0')
		dst[i + len] = src[i];
	dst[i + len] = '\0';
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*arr;
	int		len_s1;
	int		len_s2;

	if (s1 == 0 || s2 == 0)
		return (0);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	arr = (char *)malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	if (arr == 0)
		return (0);
	arr[0] = 0;
	ft_strcat(arr, s1);
	ft_strcat(arr, s2);
	return (arr);
}

char	*ft_strncat(char *s1, const char *s2, unsigned int n)
{
	char	*dest;

	dest = s1;
	if (!s1 && !s2)
		return (NULL);
	while (*dest != '\0')
		dest++;
	while (n--)
	{
		*dest++ = *s2++;
		if (!dest)
			return s1;
	}
	*dest = '\0';
	return (s1);
}

char	*ft_strdup(char *str)
{
	char	*p;
	int		i;

	i = ft_strlen(str);
	p = (char *)malloc(sizeof(char) * (i + 1));
	if (!p)
		return (NULL);
	i = -1;
	while (str[++i])
		p[i] = str[i];
	p[i] = '\0';
	return (p);
}
