#include "../includes/cube3d.h"
#include "../includes/libft.h"


#define BUFFER_SIZE 42

static char	*free_and_join(char *save, char *read)
{
	char	*join;

	join = ft_strjoin(save, read);
	free(save);
	return (join);
}

static char	*create_line(char *save)
{
	char	*line;
	size_t	i;

	i = 0;
	if (save[i] == '\0')
		return (NULL);
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	line = ft_calloc(sizeof(char), i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*put_rest(char *save)
{
	char	*rest;
	size_t	i;
	size_t	j;

	i = 0;
	while (save[i] != '\n' && save[i] != '\0')
		i++;
	if (save[i] == '\0')
	{
		free(save);
		return (NULL);
	}
	rest = ft_calloc(sizeof(char), (ft_strlen(save) - i));
	if (!rest)
		return (NULL);
	i++;
	j = 0;
	while (save[i] != '\0')
		rest[j++] = save[i++];
	rest[j] = '\0';
	free(save);
	return (rest);
}

static char	*read_file(int fd, char *save)
{
	char	*new_read;
	int		len;

	if (!save)
		save = ft_calloc(1, 1);
	new_read = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!new_read)
		return (NULL);
	len = 1;
	while (len > 0 && !ft_strchr(save, '\n'))
	{
		len = read(fd, new_read, BUFFER_SIZE);
		if (len == -1)
		{
			free(new_read);
			free(save);
			return (NULL);
		}
		new_read[len] = '\0';
		save = free_and_join(save, new_read);
	}
	free(new_read);
	return (save);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	save = read_file(fd, save);
	if (!save)
		return (NULL);
	line = create_line(save);
	save = put_rest(save);
	return (line);
}