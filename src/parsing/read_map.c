#include "../includes/cube3d.h"

t_list_map	*ft_lstnew_map(char *line);
void		ft_lstadd_back_map(t_list_map **lst, t_list_map *new);
char		**fill_array_and_free(t_list_map *lst, int size);

/* TODO: verify that trailing lines after the map
   are either empty or whitespace-only;
   they must not contain stray characters */
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
		if (!tmp)
		{
			free(line);
			while (lst)
			{
				tmp = lst;
				free(lst->line);
				lst = lst->next;
				free(tmp);
			}
			return (NULL);
		}
		ft_lstadd_back_map(&lst, tmp);
		count++;
		line = get_next_line(parse->fd);
	}
	return (fill_array_and_free(lst, count));
}