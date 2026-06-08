/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: runo <runo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:36:23 by runo              #+#    #+#             */
/*   Updated: 2026/06/08 18:36:23 by runo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	is_out_of_bounds(t_cube3d *game, t_ray *r, int map_height)
{
	int	row_len;

	if (r->map_y < 0 || r->map_y >= map_height)
		return (1);
	row_len = (int)ft_strlen(game->map[r->map_y]);
	if (r->map_x < 0 || r->map_x >= row_len)
		return (1);
	return (0);
}

void	set_tex_num(t_ray *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			r->tex_num = 2;
		else
			r->tex_num = 3;
	}
	else
	{
		if (r->ray_dir_y > 0)
			r->tex_num = 1;
		else
			r->tex_num = 0;
	}
}
