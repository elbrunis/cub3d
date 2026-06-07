#include "../../includes/cube3d.h"

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

static int	word_count(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && !is_space(s[i]))
				i++;
		}
	}
	return (count);
}

static void	frees_split(char **res, int i)
{
	while (i >= 0)
	{
		free(res[i]);
		i--;
	}
	free(res);
}

static char	*get_word(const char *s, int start, int end)
{
	char	*word;
	int		i;

	word = malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(const char *s)
{
	char	**res;
	int		i;
	int		j;
	int		start;

	if (!s)
		return (NULL);
	res = malloc(sizeof(char *) * (word_count(s) + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		start = i;
		while (s[i] && !is_space(s[i]))
			i++;
		if (i > start)
		{
			res[j] = get_word(s, start, i);
			if (!res[j])
				return (frees_split(res, j - 1), NULL);
			j++;
		}
	}
	res[j] = NULL;
	return (res);
}