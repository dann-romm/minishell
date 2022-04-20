#include "hashtable.h"
#include "libft_funcs.h"

static int	partition(char **str, int l, int r)
{
	char	*mid;
	char	*tmp;

	mid = str[(l + r) / 2];
	while (l <= r)
	{
		while (ft_strcmp(str[l], mid) < 0)
			l++;
		while (ft_strcmp(str[r], mid) > 0)
			r--;
		if (l > r)
			break;
		tmp = str[l];
		str[l] = str[r];
		str[r] = tmp;
		l++;
	}
	return (r);
}

static void	quick_sort(char **str, int l, int r)
{
	int	diff;

	diff = 0;
	if (l < r)
	{
		diff = partition(str, l, r);
		quick_sort(str, l, diff);
		quick_sort(str, diff + 1, r);
	}
}

char	**sort_hashtable(t_hashtable *ht)
{
	char	**tmp;
	int		strlen;
	int		i;

	tmp = ht_to_array(ht);
	strlen = 0;
	i = 3;
	while (tmp[strlen])
		strlen++;
	quick_sort(tmp, i, strlen - 1);
	return (tmp);
}
