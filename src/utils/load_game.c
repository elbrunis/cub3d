/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: runo <runo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:36:23 by runo              #+#    #+#             */
/*   Updated: 2026/06/08 18:36:23 by runo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static int	load_texture(void *mlx, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
		return (0);
	return (1);
}

int	load_all_textures(t_cube3d *game, t_parse *parse)
{
	if (!load_texture(game->mlx, &game->tex[0], parse->no_path))
		return (0);
	if (!load_texture(game->mlx, &game->tex[1], parse->so_path))
		return (0);
	if (!load_texture(game->mlx, &game->tex[2], parse->ea_path))
		return (0);
	if (!load_texture(game->mlx, &game->tex[3], parse->we_path))
		return (0);
	return (1);
}

void	init_player_values(t_cube3d *game, t_parse *parse)
{
	game->player->x_pos = parse->x_pos;
	game->player->y_pos = parse->y_pos;
	game->player->angle = parse->angle;
	game->player->dir_x = cos(game->player->angle);
	game->player->dir_y = sin(game->player->angle);
	game->player->plane_x = -0.66 * sin(game->player->angle);
	game->player->plane_y = 0.66 * cos(game->player->angle);
	game->player->w = false;
	game->player->s = false;
	game->player->d = false;
	game->player->a = false;
	game->player->left = false;
	game->player->right = false;
}
