/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: runo <runo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:36:23 by runo              #+#    #+#             */
/*   Updated: 2026/06/08 18:36:23 by runo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

static void	rotate_left(t_player *p)
{
	p->angle -= MOVE_ANGLE;
	if (p->angle < 0)
		p->angle += 2 * M_PI;
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
	p->plane_x = -0.66 * sin(p->angle);
	p->plane_y = 0.66 * cos(p->angle);
}

static void	rotate_right(t_player *p)
{
	p->angle += MOVE_ANGLE;
	if (p->angle > 2 * M_PI)
		p->angle -= 2 * M_PI;
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
	p->plane_x = -0.66 * sin(p->angle);
	p->plane_y = 0.66 * cos(p->angle);
}

void	move(t_cube3d *game)
{
	if (game->player->left)
		rotate_left(game->player);
	if (game->player->right)
		rotate_right(game->player);
	if (game->player->w)
		move_front(game);
	if (game->player->s)
		move_back(game);
	if (game->player->a)
		strafe_left(game);
	if (game->player->d)
		strafe_right(game);
}
