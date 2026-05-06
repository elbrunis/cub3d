#include "../includes/cube3d.h"

static char	*save_extension(t_cube3d *g, char *t, char *p)
{
	char	**dst;

	if (!ft_strncmp(t, "NO", 2))
		dst = &g->p->no_path;
	else if (!ft_strncmp(t, "SO", 2))
		dst = &g->p->so_path;
	else if (!ft_strncmp(t, "WE", 2))
		dst = &g->p->we_path;
	else
		dst = &g->p->ea_path;
	if (*dst)
		return ("Duplicate configuration detected");
	*dst = ft_strdup(p);
	g->p->n_config++;
	return (NULL);
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
	error = save_extension(game, type, split[0]);
	if (error)
		return(error);
	while (*(*line) && *(*line) != ' ' && *(*line) != '\t' && *(*line) != '\n')
		(*line)++;
	return (NULL);
}
