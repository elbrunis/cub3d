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
	parser->floor_color = (unsigned int)-1;
	parser->ceiling_color = (unsigned int)-1;
	return (parser);
}

static void	init_player_values(t_cube3d *game, t_parse *parse)
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

static int	load_all_textures(t_cube3d *game, t_parse *parse)
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

static int	allocate_game_components(t_cube3d *game)
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
	ft_memset(game, 0, sizeof(t_cube3d));
	if (!allocate_game_components(game))
	{
		free(game);
		return (NULL);
	}
	game->parse = parse;
	error = init_mlx_components(game);
	if (error)
	{
		printf("Error\n%s\n", error);
		free_game(game);
		return (NULL);
	}
	if (!load_all_textures(game, parse))
	{
		printf("Error\nFailed to load textures\n");
		free_game(game);
		return (NULL);
	}
	init_player_values(game, parse);
	game->close_game = false;
	game->map = parse->map;
	return (game);
}
