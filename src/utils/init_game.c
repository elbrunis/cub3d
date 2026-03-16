#include "../../includes/cube3d.h"

t_cube3d *init_basic(void)
{
	// TEMPORAL
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

	// TEMPORAL
	t_cube3d *game = (t_cube3d *)malloc(sizeof(t_cube3d));
	game->map = (t_map *)malloc(sizeof(t_map));
	game->map->map = map2d; // TEMPORAL
	game->map->rows = 0;
	game->map->cols = 0;
	return (game);
}