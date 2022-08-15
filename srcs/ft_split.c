static int ft_words(char const *str, char del)
{
	int i;
	int word;
	int counter;

	i = 0;
	word = 0;
	counter = 0;
	while (str[i] != '\0')
	{
		if (str[i] == del)
			word = 0;
		else
		{
			if (word == 0)
				counter++;
			word = 1;
		}
		i++;
	}
	return (counter);
}

static char *ft_strdpl(char const *str, char del, char *res, int *counter)
{
	int i;
	int size;
	int j;

	i = *counter;
	while (str[i] == del)
		i++;
	size = 0;
	while (str[i + size] != '\0' && str[i + size] != del)
		size++;
	res = (char *)malloc(sizeof(char) * (size + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (j < size)
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	*counter = i;
	return (res);
}

char **ft_split(char const *s, char c)
{
	int n_words;
	int i;
	int j;
	char **res;

	n_words = ft_words(s, c);
	res = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < n_words)
	{
		res[i] = ft_strdpl(s, c, res[i], &j);
		i++;
	}
	res[i] = 0;
	return (res);
}
