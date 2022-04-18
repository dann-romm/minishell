#include "hashtable.h"
#include "libft_funcs.h"

int	partition(char **str, int l, int r)
{
	char	*mid = str[(l + r) / 2];
	int		i = l;
	int		j = r;
	char	*tmp;
	while (i <= j) 
	{
		while (ft_strcmp(str[i], mid) < 0)
			i++;
		while (ft_strcmp(str[j], mid) > 0)
			j--;
		if (i > j)
			break;
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
	}
	return j;
}

void	quick_sort(char **str, int l, int r)
{
	int diff = 0;
	if (l < r)
	{
		diff = partition(str, l, r);
		quick_sort(str, l, diff);
		quick_sort(str, diff + 1, r);
	}
}

char	**sort_hashtable(t_hashtable *ht)
{
	char **tmp = ht_to_array(ht);
	int strlen = 0, i = 3;
	while (tmp[strlen])
		strlen++;
	quick_sort(tmp, i, strlen - 1);
	return (tmp);
}
