#include "../../includes/cube3d.h"


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
	parser->floor_color = -1;
	parser->ceiling_color = -1;
	return (parser);
}

// mover esta funcion una vez terminado todo el parseo
static void init_player_values(t_cube3d *game, t_parse *parse)
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
}

static int allocate_game_components(t_cube3d *game)
{
	game->player = (t_player *)malloc(sizeof(t_player));
	game->frame = (t_img *)malloc(sizeof(t_img));
	if (!game->player || !game->frame)
		return (0);
	return (1);
}

t_cube3d	*init_game(t_parse *parse)
{
	t_cube3d	*game;
	char		*error;

	game = (t_cube3d *)malloc(sizeof(t_cube3d));
	if (!game)
		return (NULL);
	if (!allocate_game_components(game))
	{
		free(game);
		return (NULL);
	}
	error = init_mlx_components(game);
	if (error)
	{
		printf("Error: %s\n", error);
		// poner aqui funcion para liberar el juego bien
		return (NULL);
	}
	init_player_values(game, parse);
	game->close_game = false;
	game->map = parse->map;
	return (game);
}
