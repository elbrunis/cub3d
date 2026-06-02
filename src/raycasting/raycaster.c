#include "../../includes/cube3d.h"

static int	get_tex_color(t_tex *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	dst = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

static void	draw_textured_line(t_cube3d *game, int x, t_ray *r)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		color;

	r->lineHeight = (int)(SCREEN_HEIGHT / r->perpWallDist);
	r->drawStart = (SCREEN_HEIGHT / 2) - (r->lineHeight / 2);
	r->drawEnd = (SCREEN_HEIGHT / 2) + (r->lineHeight / 2);
	if (r->drawStart < 0)
		r->drawStart = 0;
	if (r->drawEnd >= SCREEN_HEIGHT)
		r->drawEnd = SCREEN_HEIGHT - 1;
	step = (double)TEX_HEIGHT / r->lineHeight;
	tex_pos = (r->drawStart - SCREEN_HEIGHT / 2 + r->lineHeight / 2) * step;
	y = r->drawStart;
	while (y <= r->drawEnd)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		color = get_tex_color(&game->tex[r->tex_num], r->tex_x, tex_y);
		if (r->side == 1)
			color = (color >> 1) & 8355711;
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}

static void	draw_floor_ceiling(t_cube3d *game, int x, t_ray *r)
{
	int	y;

	y = 0;
	while (y < r->drawStart)
	{
		my_mlx_pixel_put(game, x, y, game->parse->ceiling_color);
		y++;
	}
	y = r->drawEnd + 1;
	while (y < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(game, x, y, game->parse->floor_color);
		y++;
	}
}

static void	calc_tex_x(t_cube3d *game, t_ray *r)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = game->player->y_pos + r->perpWallDist * r->rayDirY;
	else
		wall_x = game->player->x_pos + r->perpWallDist * r->rayDirX;
	wall_x -= floor(wall_x);
	r->tex_x = (int)(wall_x * TEX_WIDTH);
	if (r->side == 0 && r->rayDirX > 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
	if (r->side == 1 && r->rayDirY < 0)
		r->tex_x = TEX_WIDTH - r->tex_x - 1;
}

static void	select_texture(t_cube3d *game, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->rayDirX > 0)
			r->tex_num = 2;
		else
			r->tex_num = 3;
	}
	else
	{
		if (r->rayDirY > 0)
			r->tex_num = 1;
		else
			r->tex_num = 0;
	}
	(void)game;
}

static void	init_raycasting(t_cube3d *game, t_ray *r, int x)
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

static void	calculate_step(t_cube3d *game, t_ray *r)
{
	if (r->rayDirX < 0)
	{
		r->stepX = -1;
		r->sideDistX = (game->player->x_pos - r->mapX) * r->deltaDistX;
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

static void	perform_dda(t_cube3d *game, t_ray *r)
{
	int	map_height;
	int	row_len;

	map_height = 0;
	while (game->map[map_height])
		map_height++;
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
		if (r->mapY < 0 || r->mapY >= map_height)
			break ;
		row_len = (int)ft_strlen(game->map[r->mapY]);
		if (r->mapX < 0 || r->mapX >= row_len)
			break ;
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
		select_texture(game, &r);
		calc_tex_x(game, &r);
		draw_textured_line(game, x, &r);
		draw_floor_ceiling(game, x, &r);
		x++;
	}
}
