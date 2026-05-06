#include "../../includes/cube3d.h"

// mapa temporal
static void	map_temporal(t_cube3d *game)
{
	static char	*map2d[] = {
		"1111111111111111111111111",
		"1000000000110000000000001",
		"1011111100110011111111001",
		"1010000100000010000001001",
		"1010100100110010111101001",
		"1010111100110010000101001",
		"1000000000000011111100001",
		"1111111111001111000000001",
		"1000000011001100001111111",
		"1011110011000000111100001",
		"1000110000001100000000001",
		"1111111111111111111111111",
		NULL
	};

	game->map->map = map2d;
}

void	init_parser(t_parser *parser)
{
	if (!parser)
		return;
	parser->fd = 0;
	parser->n_config = 0;
	parser->no_path = NULL;
	parser->so_path = NULL;
	parser->we_path = NULL;
	parser->ea_path = NULL;
	parser->player_set = false;
	parser->floor_color = -1;
	parser->ceiling_color = -1;
}

// mover esta funcion una vez terminado todo el parseo
static void	init_player_values(t_cube3d *game)
{
	game->player->x_pos = 5.0;
	game->player->y_pos = 5.0;
	game->player->angle = 0.0;
	game->player->dir_x = cos(game->player->angle);
	game->player->dir_y = sin(game->player->angle);
	game->player->plane_x = -0.66 * sin(game->player->angle);
	game->player->plane_y = 0.66 * cos(game->player->angle);
	game->player->w = false;
	game->player->s = false;
	game->player->d = false;
	game->player->a = false;
}

t_cube3d	*init_basic(void)
{
	t_cube3d	*game;

	game = (t_cube3d *)malloc(sizeof(t_cube3d));
	if (!game)
		return (NULL);
	game->map = (t_map *)malloc(sizeof(t_map));
	game->player = (t_player *)malloc(sizeof(t_player));
	game->frame = (t_img *)malloc(sizeof(t_img));
    game->p = (t_parser *)malloc(sizeof(t_parser));
	if (!game->map || !game->player || !game->frame || !game->p)
		return (NULL);
	game->close_game = false;
	init_parser(game->p);
	init_player_values(game);
	init_window(game);
	map_temporal(game);
	game->map->rows = 0;
	game->map->cols = 0;
	game->frame->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->frame->addr = mlx_get_data_addr(game->frame->img,
			&game->frame->bits_per_pixel, &game->frame->line_length,
			&game->frame->endian);
	return (game);
}
