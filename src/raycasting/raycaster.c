#include "../../includes/cube3d.h"

/* 
	falta por reducir 2 lineas aqui
*/
void	print_3d(t_cube3d *game, int x, t_ray *r, int color)
{
	int	y;

	r->lineHeight = (int)(SCREEN_HEIGHT / r->perpWallDist);
	r->drawStart = (SCREEN_HEIGHT / 2) - (r->lineHeight / 2);
	r->drawEnd = (SCREEN_HEIGHT / 2) + (r->lineHeight / 2);
	if (r->drawStart < 0)
		r->drawStart = 0;
	if (r->drawEnd >= SCREEN_HEIGHT)
		r->drawEnd = SCREEN_HEIGHT - 1;
	if (r->side == 1)
		color = color / 2;
	y = 0;
	while (y < r->drawStart)
	{
		my_mlx_pixel_put(game, x, y, 0x333333);
		y++;
	}
	while (y <= r->drawEnd)
	{
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(game, x, y, 0x555555);
		y++;
	}
}

void	init_raycasting(t_cube3d *game, t_ray *r, int x)
{
	ft_memset(r, 0, sizeof(t_ray));

	r->cameraX = (2 * x / (double)SCREEN_WIDTH) - 1;
	r->rayDirX = game->player->dir_x + (game->player->plane_x * r->cameraX);
	r->rayDirY = game->player->dir_y + (game->player->plane_y * r->cameraX);

	r->mapX = (int)game->player->x_pos;
	r->mapY = (int)game->player->y_pos;

	if (r->rayDirX == 0)
		r->deltaDistX = 1e30;
	else
		r->deltaDistX = fabs(1 / r->rayDirX);

	if (r->rayDirY == 0)
		r->deltaDistY = 1e30;
	else
		r->deltaDistY = fabs(1 / r->rayDirY);
}

void	calculate_step(t_cube3d *game, t_ray *r)
{
	if (r->rayDirX < 0)
	{
		r->stepX = -1;
		r->sideDistX = (game->player->x_pos - r->mapX) * r->deltaDistX; // aqui tengo q calcular el lado mas cercano ya que estamos en lo negativo nor lo q es como si fueramos hacia atras
	}
	else 
	{
		r->stepX = 1;
		r->sideDistX = (r->mapX + 1.0 - game->player->x_pos) * r->deltaDistX;
	}
	if (r->rayDirY < 0)
	{
		r->stepY = -1;
		r->sideDistY = (game->player->y_pos - r->mapY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = (r->mapY + 1.0 - game->player->y_pos) * r->deltaDistY;
	}
}

void	perform_dda(t_cube3d *game, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (game->map[r->mapY][r->mapX] == '1')
			r->hit = 1;
	}
	if (r->side == 0)
		r->perpWallDist = r->sideDistX - r->deltaDistX;
	else
		r->perpWallDist = r->sideDistY - r->deltaDistY;
}

void	raycasting(t_cube3d *game)
{
	t_ray	r;
	int		x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_raycasting(game, &r, x);
		calculate_step(game, &r);
		perform_dda(game, &r);
		print_3d(game, x, &r, 0xFFFFFF);
		x++;	
	}
}

