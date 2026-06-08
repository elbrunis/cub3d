/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_walk.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: runo <runo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:36:23 by runo              #+#    #+#             */
/*   Updated: 2026/06/08 18:36:23 by runo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	move_front(t_cube3d *game)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = game->player;
	new_x = p->x_pos + (p->dir_x * SPEED);
	new_y = p->y_pos + (p->dir_y * SPEED);
	if (!is_blocked(game, new_x, p->y_pos))
		p->x_pos = new_x;
	if (!is_blocked(game, p->x_pos, new_y))
		p->y_pos = new_y;
}

void	move_back(t_cube3d *game)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = game->player;
	new_x = p->x_pos - (p->dir_x * SPEED);
	new_y = p->y_pos - (p->dir_y * SPEED);
	if (!is_blocked(game, new_x, p->y_pos))
		p->x_pos = new_x;
	if (!is_blocked(game, p->x_pos, new_y))
		p->y_pos = new_y;
}

void	strafe_right(t_cube3d *game)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = game->player;
	new_x = p->x_pos - (p->dir_y * SPEED);
	new_y = p->y_pos + (p->dir_x * SPEED);
	if (!is_blocked(game, new_x, p->y_pos))
		p->x_pos = new_x;
	if (!is_blocked(game, p->x_pos, new_y))
		p->y_pos = new_y;
}

void	strafe_left(t_cube3d *game)
{
	t_player	*p;
	double		new_x;
	double		new_y;

	p = game->player;
	new_x = p->x_pos + (p->dir_y * SPEED);
	new_y = p->y_pos - (p->dir_x * SPEED);
	if (!is_blocked(game, new_x, p->y_pos))
		p->x_pos = new_x;
	if (!is_blocked(game, p->x_pos, new_y))
		p->y_pos = new_y;
}
