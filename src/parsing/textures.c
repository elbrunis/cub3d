#include "../includes/cube3d.h"

static void	save_extension(t_cube3d *game, char *type, char *path)
{
	if (ft_strncmp(type, "NO", 2) == 0)
		game->p->no_path = ft_strdup(path);
	else if (ft_strncmp(type, "SO", 2) == 0)
		game->p->so_path = ft_strdup(path);
	else if (ft_strncmp(type, "WE", 2) == 0)
		game->p->we_path = ft_strdup(path);
	else if (ft_strncmp(type, "EA", 2) == 0)
		game->p->ea_path = ft_strdup(path);
	game->p->n_config++;
}

static char	*check_line_format(char *line)
{
	if (line[2] != ' ')
		return ("There is an empty texture or a missing space");
	if (line[3] == '\0' || line[3] == ' ' || line[3] == '\t')
		return ("There is an empty or misspelled texture");
	return (NULL);
}

static int	valid_extension(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len < 5)
		return (0);
	return (str[len - 1] == 'm'
		&& str[len - 2] == 'p'
		&& str[len - 3] == 'x'
		&& str[len - 4] == '.');
}

static char	*check_texture(char **split)
{
	int	fd;

	if (ft_splitlen(split) > 1)
		return ("There are invalid characters after the texture");
	if (!valid_extension(split[0]))
		return ("One of the texture extensions is invalid");
	fd = open(split[0], O_RDONLY);
	if (fd < 0)
		return ("One of the textures could not be opened");
	close(fd);
	return (NULL);
}

char	*get_extension(t_cube3d *game, char **line, char *type)
{
	char	**split;
	char	*error;

	(void)game;
	error = check_line_format((*line));
	if (error)
		return (error);
	split = ft_split((*line) + 2);
	if (!split || !split[0])
		return ("split error");
	error = check_texture(split);
	if (error)
	{
		free_split(split);
		return (error);
	}
	save_extension(game, type, split[0]);
	while (*(*line) && *(*line) != ' ' && *(*line) != '\t' && *(*line) != '\n')
		(*line)++;
	return (NULL);
}
