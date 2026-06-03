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

/* falta por arreglar esta funcion para q coja y verifique si las
ultimas lineas son validas osea pueden tener slatos de lineas
pero no caracteres sueltos vacios*/
char	**read_map(t_parse *parse)
{
	t_list_map	*lst;
	t_list_map	*tmp;
	char		*line;
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
	return (fill_array_and_free(lst, count));
}

