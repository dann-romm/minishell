unsigned int	djb2_hash(char *key, unsigned int size)
{
	unsigned int	hash;
	int				i;

	hash = 5381;
	i = -1;
	while (key[++i])
		hash = (hash << 5) + hash + (unsigned int)key[i];
	return (hash % size);
}
