#include "../../includes/cube3d.h"

static void draw_line(t_cube3d *game, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(game, x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 < dx)  { err += dx; y0 += sy; }
    }
}

void	raycasting(t_cube3d *game)
{
	int	x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		double cameraX = (2 * x / (double)SCREEN_WIDTH) - 1;
		double rayDirX = game->player->dir_x + (game->player->plane_x * cameraX);
		double rayDirY = game->player->dir_y + (game->player->plane_y * cameraX);
	
		int mapX = (int)game->player->x_pos;
		int mapY = (int)game->player->y_pos;

		double deltaDistX;
		if (rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX); // el fabs pasa el numero a positivo

		double deltaDistY;
		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY); // el fabs pasa el numero a positivo
		
		int stepX, stepY;
		double sideDistX, sideDistY;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game->player->x_pos - mapX) * deltaDistX;
		}
		else 
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->player->x_pos) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game->player->y_pos - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->player->y_pos) * deltaDistY;
		}

		int hit = 0;
		int side;
		while (hit == 0)
		{
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (game->map->map[mapY][mapX] == '1')
				hit = 1;
		}
		//
	double perpWallDist;
	if (side == 0)
		perpWallDist = sideDistX - deltaDistX;
	else
		perpWallDist = sideDistY - deltaDistY;

	// PUNTO EXACTO DE IMPACTO EN EL BORDE DE LA PARED
	double wallHitX, wallHitY;
	if (side == 0)
	{
    	// Si el rayo va a la derecha, el borde que toca es el izquierdo de mapX
   		// Si el rayo va a la izquierda, el borde que toca es el derecho de mapX (mapX + 1)
    	if (rayDirX > 0)
        	wallHitX = mapX * SQUARE_LEN;
    	else
        	wallHitX = (mapX + 1) * SQUARE_LEN;
    	wallHitY = (game->player->y_pos + perpWallDist * rayDirY) * SQUARE_LEN;
	}
	else
	{
	    wallHitX = (game->player->x_pos + perpWallDist * rayDirX) * SQUARE_LEN;
	    // Si el rayo va hacia abajo, el borde que toca es el superior de mapY
	    // Si el rayo va hacia arriba, el borde que toca es el inferior de mapY (mapY + 1)
	    if (rayDirY > 0)
	        wallHitY = mapY * SQUARE_LEN;
	    else
	        wallHitY = (mapY + 1) * SQUARE_LEN;
	}

	int playerPixelX = (int)(game->player->x_pos * SQUARE_LEN);
	int playerPixelY = (int)(game->player->y_pos * SQUARE_LEN);

	if (x % 10 == 0)
		draw_line(game, playerPixelX, playerPixelY, (int)wallHitX, (int)wallHitY, ORANGE);
		//
		x++;
	}
}