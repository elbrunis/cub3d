/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: runo <runo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:36:23 by runo              #+#    #+#             */
/*   Updated: 2026/06/08 18:36:23 by runo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_parse(t_parse *parse)
{
	if (!parse)
		return ;
	if (parse->no_path)
		free(parse->no_path);
	if (parse->so_path)
		free(parse->so_path);
	if (parse->we_path)
		free(parse->we_path);
	if (parse->ea_path)
		free(parse->ea_path);
	if (parse->map)
		free_map(parse->map);
	free(parse);
}

static void	free_textures(t_cube3d *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->tex[i].img)
			mlx_destroy_image(game->mlx, game->tex[i].img);
		i++;
	}
}

static void	free_game_resources(t_cube3d *game)
{
	if (game->win && game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		game->win = NULL;
	}
	if (game->mlx)
		free_textures(game);
	if (game->frame)
	{
		if (game->frame->img && game->mlx)
			mlx_destroy_image(game->mlx, game->frame->img);
		free(game->frame);
		game->frame = NULL;
	}
	if (game->player)
	{
		free(game->player);
		game->player = NULL;
	}
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

bool	free_game(t_cube3d *game)
{
	if (!game)
		return (false);
	free_game_resources(game);
	free_parse(game->parse);
	free(game);
	return (true);
}