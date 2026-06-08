/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: runo <runo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:36:23 by runo              #+#    #+#             */
/*   Updated: 2026/06/08 18:36:23 by runo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	my_mlx_pixel_put(t_cube3d *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = game->frame->addr + (y * game->frame->line_length + x * \
		(game->frame->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int		x_pres(void *data)
{
	t_cube3d	*game;

	game = (t_cube3d *)data;
	game->close_game = true;
	return (0);
}


char	*init_mlx_components(t_cube3d *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return ("mlx_init failed");
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!game->win)
		return ("mlx_new_window failed");
	game->frame->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->frame->img)
		return ("mlx_new_image failed");
	game->frame->addr = mlx_get_data_addr(game->frame->img,
			&game->frame->bits_per_pixel, &game->frame->line_length,
			&game->frame->endian);
	if (!game->frame->addr)
		return ("mlx_get_data_addr failed");
	return (NULL);
}
