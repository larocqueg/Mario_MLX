/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gabriel <gabriel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 16:38:05 by gabriel           #+#    #+#             */
/*   Updated: 2026/06/17 16:38:45 by gabriel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_putstr_fd("ERROR, Usage: ./mario maps/1-1.ber", 2);
		return (0);
	}
	if (!check_args(av[1]))
	{
		ft_printf("Error, Could not read file!\n");
		return (0);
	}
	game_init(&game);
	init_window(&game);
	get_textures(&game);
	ft_load_map(av[1], &game);
	get_player_pos(&game);
	game.map_width = ft_strlen(game.map[0]);
	mlx_hook(game.win_ptr, DestroyNotify, (1L<<17), free_displays, &game);
	mlx_hook(game.win_ptr, 02, (1L<<0), key_pressed, &game);
	mlx_hook(game.win_ptr, 03, (1L<<1), key_released, &game);
	mlx_loop_hook(game.mlx_ptr, game_loop, &game);
	mlx_loop(game.mlx_ptr);
}



