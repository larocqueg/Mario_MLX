/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:03:20 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/04 11:41:49 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	game_init(t_game *game)
{
	game->fd = 0;
	game->map = NULL;
	game->map_height = 15;
	game->map_width = 0;
	game->delta = 0;
	game->player.jump = false;
	game->player.big = false;
	game->cameraX = 0;
	game->started = false;
	game->multiplayer = false;
	game->player.is_on_ground = true;
	game->player.velocity = (t_point){0, 0};
	game->player.direction.x = 0;
	game->player.direction.y = 0;
	game->power_up_frames = 0;
	game->player.current_frame = 0;
	game->last_frame_time = get_time();
	game->player.left = false;
	game->player.current_frame = 0;
	game->player.animation_state = IDLE;
	game->player.running = false;
	game->player.holding = false;
	game->player.falling = false;
	game->player.dying = false;
	game->ended_p1 = false;
	game->ended_p2 = false;
	for (int i = 0; i < 24; i++)
	{
		game->goombas[i].exist = false;
		game->goombas[i].is_on_ground = true;
		game->goombas[i].left = true;
		game->goombas[i].started = false;
		game->goombas[i].stopped = false;
		game->goombas[i].stopped = false;
	}
	game->player2.jump = false;
	game->player2.big = false;
	game->player2.is_on_ground = true;
	game->player2.velocity = (t_point){0, 0};
	game->player2.direction.x = 0;
	game->player2.direction.y = 0;
	game->player2.current_frame = 0;
	game->player2.left = false;
	game->player2.current_frame = 0;
	game->player2.animation_state = IDLE;
	game->player2.running = false;
	game->player2.holding = false;
	game->player2.falling = false;
	game->player2.dying = false;
}

void	get_player_pos(t_game *game)
{
	int x = 0;
	int	y = 0;
	int	G = 0;

	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (ft_strchr("M", game->map[y][x]))
			{
				game->player.pos.x = x;
				game->player.pos.y = y;
				game->player2.pos.x = x + 1;
				game->player2.pos.y = y;
				game->player.hit_block = false;
				game->player.hit_cooldown = 0;
				game->player.hit = (t_point){-1, -1};
				game->player2.hit_block = false;
				game->player2.hit_cooldown = 0;
				game->player2.hit = (t_point){-1, -1};
			}
			else if (ft_strchr("G", game->map[y][x]))
			{
				game->goombas[G].pos.x = x;
				game->goombas[G].pos.y = y;
				game->goombas[G].exist = true;
				game->goombas[G].is_on_ground = true;
				game->goombas[G].left = true;
				game->goombas[G].gravity = 0;
				game->goombas[G].direction.x = -1;
				game->goombas[G].started = false;
				game->goombas[G].despawn = 0;
				game->goombas[G].collision = true;
				game->goombas[G].outofgame = false;
				G++;
			}
			else if (ft_strchr("F", game->map[y][x]))
			{
				game->flag_pos = x;
			}
			else if (ft_strchr("C", game->map[y][x]))
			{
				game->castle_pos = x + 2;
			}
			x++;
		}
		y++;
	}
	game->goomba_count = G;
}
