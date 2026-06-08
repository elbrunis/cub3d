/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: runo <runo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:36:23 by runo              #+#    #+#             */
/*   Updated: 2026/06/08 18:36:23 by runo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_list_map	*ft_lstnew_map(char *line)
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

void	ft_lstadd_back_map(t_list_map **lst, t_list_map *new)
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

char	**fill_array_and_free(t_list_map *lst, int size)
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