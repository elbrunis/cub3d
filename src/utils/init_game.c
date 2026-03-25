#include "../../includes/cube3d.h"

// FUNCION TEMPORAL
static void map_temporal(t_cube3d *game)
{
    static char *map2d[] = {
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
    game->map->map = map2d; // TEMPORAL
}




t_cube3d *init_basic(void)
{
    t_cube3d *game = (t_cube3d *)malloc(sizeof(t_cube3d));
    game->map = (t_map *)malloc(sizeof(t_map));
    game->player = (t_player *)malloc(sizeof(t_player));
    game->frame = (t_img *)malloc(sizeof(t_img));
    game->close_game = false;

    //temporal
    game->player->x_pos = 5.0;
    game->player->y_pos = 5.0;

    game->player->angle = 0.0;

    game->player->dir_x = cos(game->player->angle); // Esto dará 1.0
    game->player->dir_y = sin(game->player->angle); // Esto dará 0.0    
    game->player->w = false;
    game->player->s = false;
    game->player->d = false;
    game->player->a = false;
    //temporal

    init_window(game);
    map_temporal(game);// temporal
    game->map->rows = 0;
    game->map->cols = 0;

    game->frame->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->frame->addr =mlx_get_data_addr(game->frame->img, &game->frame->bits_per_pixel, 
                                   &game->frame->line_length, &game->frame->endian);
    return (game);
}