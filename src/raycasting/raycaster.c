/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: runo <runo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:36:23 by runo              #+#    #+#             */
/*   Updated: 2026/06/08 18:36:23 by runo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	init_raycasting(t_cube3d *game, t_ray *r, int x)
{
	ft_memset(r, 0, sizeof(t_ray));
	r->camera_x = (2 * x / (double)SCREEN_WIDTH) - 1;
	r->ray_dir_x = game->player->dir_x + (game->player->plane_x * r->camera_x);
	r->ray_dir_y = game->player->dir_y + (game->player->plane_y * r->camera_x);
	r->map_x = (int)game->player->x_pos;
	r->map_y = (int)game->player->y_pos;
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1 / r->ray_dir_y);
}

static void	calculate_step(t_cube3d *game, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (game->player->x_pos - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0
				- game->player->x_pos) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (game->player->y_pos - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0
				- game->player->y_pos) * r->delta_dist_y;
	}
}

static void	run_dda_loop(t_cube3d *game, t_ray *r, int map_height)
{
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (is_out_of_bounds(game, r, map_height))
			break ;
		if (game->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

static void	perform_dda(t_cube3d *game, t_ray *r)
{
	int	map_height;

	map_height = 0;
	while (game->map[map_height])
		map_height++;
	run_dda_loop(game, r, map_height);
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
}

void	raycasting(t_cube3d *game)
{
	t_ray	r;
	int		x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_raycasting(game, &r, x);
		calculate_step(game, &r);
		perform_dda(game, &r);
		calc_tex_x(game, &r);
		draw_textured_line(game, x, &r);
		draw_floor_ceiling(game, x, &r);
		x++;
	}
}
