#include "../includes/cube3d.h"


static void	free_map_list(t_list_map *lst)
{
	t_list_map	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

static void	clean_line(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static t_list_map	*ft_lstnew_map(char *line)
{
	t_list_map	*new;

	new = malloc(sizeof(t_list_map));
	if (!new)
		return (NULL);
	clean_line(line);
	new->line = line;
	new->next = NULL;
	return (new);
}

static void	ft_lstadd_back_map(t_list_map **lst, t_list_map *new)
{
	t_list_map	*curr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

static char	**fill_array_and_free(t_list_map *lst, int size)
{
	char		**map;
	t_list_map	*head;
	int			i;

	map = malloc(sizeof(char *) * (size + 1));
	if (!map)
		return (NULL);
	head = lst;
	i = 0;
	while (lst)
	{
		map[i] = lst->line;
		lst = lst->next;
		i++;
	}
	map[i] = NULL;
	free_map_list(head);
	return (map);
}

static void	pad_map_rows(char **map)
{
	int		max_width;
	int		current_len;
	int		i;
	int		j;
	char	*padded;

	max_width = 0;
	i = -1;
	while (map[++i])
	{
		current_len = (int)ft_strlen(map[i]);
		if (current_len > max_width)
			max_width = current_len;
	}
	i = -1;
	while (map[++i])
	{
		current_len = (int)ft_strlen(map[i]);
		if (current_len < max_width)
		{
			padded = malloc(max_width + 1);
			if (!padded)
				return ;
			j = -1;
			while (map[i][++j])
				padded[j] = map[i][j];
			while (j < max_width)
				padded[j++] = ' ';
			padded[j] = '\0';
			free(map[i]);
			map[i] = padded;
		}
	}
}

char	**read_map(t_parse *parse)
{
	t_list_map	*lst;
	t_list_map	*tmp;
	char		*line;
	char		**map;
	int			count;

	lst = NULL;
	count = 0;
	line = get_next_line(parse->fd);
	while (line)
	{
		tmp = ft_lstnew_map(line);
		ft_lstadd_back_map(&lst, tmp);
		count++;
		line = get_next_line(parse->fd);
	}
	if (!lst)
		return (NULL);
	map = fill_array_and_free(lst, count);
	if (map)
		pad_map_rows(map);
	return (map);
}

