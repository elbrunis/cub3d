/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: runo <runo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 18:36:23 by runo              #+#    #+#             */
/*   Updated: 2026/06/08 18:36:23 by runo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

static void	print_error(const char *msg)
{
	if (errno != 0)
		printf("Error\n%s: %s\n", msg, strerror(errno));
	else
		printf("Error\n%s\n", msg);
}

static int	game_loop(void *data)
{
	t_cube3d	*game;

	game = (t_cube3d *)data;
	if (game->close_game)
	{
		mlx_loop_end(game->mlx);
		return (0);
	}
	move(game);
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cube3d		*game;
	t_parse			*parse;
	const char		*error;

	if (argc != 2)
		return (printf("Error\nmissing arguments\n"));
	parse = init_parser();
	if (!parse)
		return (1);
	error = parser(parse, argv[1]);
	if (error)
	{
		print_error(error);
		free_parse(parse);
		return (1);
	}
	game = init_game(parse);
	if (!game)
		return (1);
	mlx_hook(game->win, 2, 1L << 0, press_key, (void *)game);
	mlx_hook(game->win, 3, 1L << 1, release_key, (void *)game);
	mlx_hook(game->win, 17, 0, x_pres, (void *)game);
	mlx_loop_hook(game->mlx, game_loop, (void *)game);
	mlx_loop(game->mlx);
	free_game(game);
	return (0);
}
