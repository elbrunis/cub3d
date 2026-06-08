/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: runo <runo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:36:23 by runo              #+#    #+#             */
/*   Updated: 2026/06/08 18:36:23 by runo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	get_tex_color(t_tex *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static void	calc_wall_bounds(t_ray *r)
{
	if (r->perp_wall_dist < 0.0001)
		r->perp_wall_dist = 0.0001;
	r->line_height = (int)(SCREEN_HEIGHT / r->perp_wall_dist);
	r->draw_start = (SCREEN_HEIGHT / 2) - (r->line_height / 2);
	r->draw_end = (SCREEN_HEIGHT / 2) + (r->line_height / 2);
	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
}

void	draw_textured_line(t_cube3d *game, int x, t_ray *r)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;

	calc_wall_bounds(r);
	step = (double)TEX_HEIGHT / r->line_height;
	tex_pos = (r->draw_start - SCREEN_HEIGHT / 2 + r->line_height / 2) * step;
	y = r->draw_start;
	while (y <= r->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = get_tex_color(&game->tex[r->tex_num], r->tex_x, tex_y);
		if (r->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}

void	draw_floor_ceiling(t_cube3d *game, int x, t_ray *r)
{
	int	y;

	if (r->draw_start < 0)
		r->draw_start = 0;
	if (r->draw_start > SCREEN_HEIGHT)
		r->draw_start = SCREEN_HEIGHT;
	if (r->draw_end < 0)
		r->draw_end = 0;
	if (r->draw_end >= SCREEN_HEIGHT)
		r->draw_end = SCREEN_HEIGHT - 1;
	y = 0;
	while (y < r->draw_start)
	{
		my_mlx_pixel_put(game, x, y, game->parse->ceiling_color);
		y++;
	}
	y = r->draw_end + 1;
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(game, x, y, game->parse->floor_color);
		y++;
	}
}

void	calc_tex_x(t_cube3d *game, t_ray *r)
{
	double	wall_x;

	set_tex_num(r);
	if (r->side == 0)
		wall_x = game->player->y_pos + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = game->player->x_pos + r->perp_wall_dist * r->ray_dir_x;
	wall_x -= floor(wall_x);
	r->tex_x = (int)(wall_x * TEX_WIDTH);
	if (r->side == 0 && r->ray_dir_x > 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
}
