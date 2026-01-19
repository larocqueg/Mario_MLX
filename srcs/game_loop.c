/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:06:28 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/08 18:42:28 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	update(t_game *game)
{
	calculate_Delta(game);
	if (game->started)
	{
		move_enemies(game);
		move(game);
		if (game->multiplayer)
		{
			move_player_2(game);
			if ((int)game->player.pos.x >= (int)game->castle_pos
				&& (int)game->player2.pos.x >= (int)game->castle_pos
				|| ((int)game->player.pos.y >= 20 && (int)game->player2.pos.y >= 20))
					free_displays(game);
		  }
		else if ((int)game->player.pos.x >= (int)game->castle_pos
			|| (int)game->player.pos.y >= 20)
			free_displays(game);
	}
	animation_times(game);
	return (1);
}

int	renderer(t_game *game)
{
	memcpy(game->image.addr, game->background.addr, game->background.line_length * SCREEN_SIZE_Y );
	drawmap(game);
	if (!game->started)
	{
		drawtexture(game, (t_point){SCREEN_SIZE_X / 4, SCREEN_SIZE_Y / 7}, &game->title_screen, SCALE);
		if (game->multiplayer)
		{
			drawtexture(game, (t_point){SCREEN_SIZE_X / 3, SCREEN_SIZE_Y - SCREEN_SIZE_Y / 3.05}, &game->selector, SCALE);
		}
		else
		{
			drawtexture(game, (t_point){SCREEN_SIZE_X / 3, SCREEN_SIZE_Y - SCREEN_SIZE_Y / 2.55}, &game->selector, SCALE);
		}
	}
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->image.img, 0, 0);
	return (1);
}

int	game_loop(t_game *game)
{
	update(game);
	renderer(game);
	return (1);
}
