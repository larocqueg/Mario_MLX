/* ************************************************************************** */
/*    */
/*  :::::::::::   */
/*   main.c   :+::+:    :+:   */
/*    +:+ +:+   +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+ +#+  */
/*+#+#+#+#+#+   +#+     */
/*   Created: 2025/01/25 17:42:20 by rafaelfe    #+#    #+# */
/*   Updated: 2025/05/15 16:45:52 by rafaelfe   ###   ########.fr */
/*    */
/* ************************************************************************** */

#include "../includes/game.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (0);
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



