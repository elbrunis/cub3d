/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: runo <runo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:36:23 by runo              #+#    #+#             */
/*   Updated: 2026/06/08 18:36:23 by runo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	load_all_textures(t_cube3d *game, t_parse *parse);
void	init_player_values(t_cube3d *game, t_parse *parse);

static int	allocate_game_components(t_cube3d *game)
{
	game->player = (t_player *)malloc(sizeof(t_player));
	game->frame = (t_img *)malloc(sizeof(t_img));
	if (!game->player || !game->frame)
		return (0);
	return (1);
}

static int	setup_resources(t_cube3d *game, t_parse *parse)
{
	char	*error;

	error = init_mlx_components(game);
	if (error)
	{
		printf("Error\n%s\n", error);
		return (0);
	}
	if (!load_all_textures(game, parse))
	{
		printf("Error\nFailed to load textures\n");
		return (0);
	}
	return (1);
}

t_parse	*init_parser(void)
{
	t_parse	*parser;

	parser = (t_parse *)malloc(sizeof(t_parse));
	if (!parser)
		return (NULL);
	parser->fd = 0;
	parser->n_config = 0;
	parser->map = NULL;
	parser->x_pos = 0.0;
	parser->y_pos = 0.0;
	parser->angle = 0.0;
	parser->no_path = NULL;
	parser->so_path = NULL;
	parser->we_path = NULL;
	parser->ea_path = NULL;
	parser->player_set = false;
	parser->floor_color = (unsigned int)-1;
	parser->ceiling_color = (unsigned int)-1;
	return (parser);
}

t_cube3d	*init_game(t_parse *parse)
{
	t_cube3d	*game;

	game = (t_cube3d *)malloc(sizeof(t_cube3d));
	if (!game)
		return (NULL);
	ft_memset(game, 0, sizeof(t_cube3d));
	if (!allocate_game_components(game))
	{
		free(game);
		return (NULL);
	}
	game->parse = parse;
	if (!setup_resources(game, parse))
	{
		free_game(game);
		return (NULL);
	}
	init_player_values(game, parse);
	game->close_game = false;
	game->map = parse->map;
	return (game);
}