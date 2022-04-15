#include "libft_funcs.h"

int	is_alpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	is_numeric(char c)
{
	return (c >= '0' && c <= '9');
}

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

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (dst);
	if ((unsigned long long)dst < (unsigned long long)src)
	{
		i = 0;
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	else
	{
		while (len--)
			((char *)dst)[len] = ((char *)src)[len];
	}
	return (dst);
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
	n = ABS(n);
	while (n > 0)
	{
		str[len--] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}

char	**adapt_cmd_args(t_simple_cmd *command)
{
	int i = 0;
	int j = 0;
	char **new = (char **)malloc(sizeof(char *) * (command->args_num + 2));
	if (new == 0)
		return (0);
	new[i] = ft_strdup(command->cmd);
	i++;
	while (i <= command->args_num)
	{
		new[i] = ft_strdup(command->cmd_args[j]);
		i++;
		j++;
	}
	new[i] = 0;
	return (new);
}

char *three_str_cat(char *s1, char *s2, char *s3)
{
	int		len;
	int		i;
	int		j;
	char	*dest;
	
	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	while (s1[i] && i < (len + 1))
	{
		dest[i] = s1[i];
		i++;
	}
	while (s2[j] && i < (len + 1))
		dest[i++] = s2[j++];
	j = 0;
	while (s3[j] && i < (len + 1))
		dest[i++] = s3[j++];
	dest[i] = '\0';
	return (dest);
}

char **ht_to_array(t_hashtable *ht)
{
	int		i;
	int		j;
	char	**env_array;
	t_pair	*pair;

	i = -1;
	j = 0;
	env_array = (char **)malloc(sizeof(char *) * (length_hashtable(ht) + 1));
	while (++i < ht->size)
	{
		pair = ht->table[i];
		while (pair)
		{
			env_array[j] = three_str_cat(pair->key, "=", pair->value);
			j++;
			pair = pair->next;
		}
	}
	env_array[j] = 0;
	return (env_array);
}

void	perror_exit(char *message)
{
	perror(message);
	exit(1);
}

char	*find_path(t_simple_cmd *command)
{
	int i = -1;
	int all = -1;
	char *cur_dir = find_hashtable(g_shell->env_global, "PWD");
	cur_dir = three_str_cat(cur_dir, "/", command->cmd);
	all = access(cur_dir, F_OK);
	if (all == 0)
		return (cur_dir);
	free(cur_dir);
	char **paths = ft_split(find_hashtable(g_shell->env_global, "PATH"), ':');
	while (paths[++i])
	{
		cur_dir = three_str_cat(paths[i], "/", command->cmd);
		all = access(cur_dir, F_OK);
		if (all == 0)
		{
			free_2d_array(paths);
			return (cur_dir);
		}
		free(cur_dir);
	}
	// сюда попадаем, когда ни одна директория из PATH не содержит бинарника
	free_2d_array(paths);
	printf("minishell: %s: command not found\n", command->cmd);
	return (0);
}
