#include "../../includes/cube3d.h"


void print_3d(t_cube3d *game, int column, double perpWallDist, int side, int color)
{
    int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
    int drawStart = (SCREEN_HEIGHT / 2) - (lineHeight / 2);
    int drawEnd   = (SCREEN_HEIGHT / 2) + (lineHeight / 2);

    if (drawStart < 0) drawStart = 0;
    if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

    if (side == 1)
        color = color / 2;

    // techo
    int y = 0;
    while (y < drawStart)
    {
        my_mlx_pixel_put(game, column, y, 0x333333);
        y++;
    }
    // pared
    while (y <= drawEnd)
    {
        my_mlx_pixel_put(game, column, y, color);
        y++;
    }
    // suelo
    while (y < SCREEN_HEIGHT)
    {
        my_mlx_pixel_put(game, column, y, 0x555555);
        y++;
    }
}


/*
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
}*/

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
        	wallHitX = (float)mapX;
    	else
        	wallHitX = (float)mapX + 1;
    	wallHitY = game->player->y_pos + perpWallDist * rayDirY;
	}
	else
	{
	    wallHitX = game->player->x_pos + perpWallDist * rayDirX;
	    // Si el rayo va hacia abajo, el borde que toca es el superior de mapY
	    // Si el rayo va hacia arriba, el borde que toca es el inferior de mapY (mapY + 1)
	    if (rayDirY > 0)
	        wallHitY = (float)mapY;
	    else
	        wallHitY = (float)mapY + 1;
	}

	int playerX = game->player->x_pos;
	int playerY = game->player->y_pos;

	print_3d(game, x, perpWallDist, side, 0xFFFFFF);

	//if (x % 10 == 0)
		//draw_line(game, playerPixelX, playerPixelY, (int)wallHitX, (int)wallHitY, ORANGE);
		//
		x++;
	}
}