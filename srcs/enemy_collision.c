/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:39:19 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/09 00:32:51 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	enemy_collision(t_game *game, t_enemy *enemy, t_point newpos)
{
	if (!enemy->collision)
	{
		enemy->pos.x = newpos.x;
		enemy->pos.y = newpos.y;
		return ;
	}
	if (enemy->direction.x <= 0)
	{
		if (ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.0f, enemy->pos.y + 0.0f)) || ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.0f, enemy->pos.y + 0.9f)))
		{
			newpos.x = (int)newpos.x + 1;
			enemy->direction.x *= -1;
		}

	}
	else
	{
		if (ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 1.0f, enemy->pos.y + 0.0f)) || ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 1.0f, enemy->pos.y + 0.9)))
		{

			newpos.x = (int)newpos.x;
			enemy->direction.x *= -1;

		}
	}
	if (enemy->gravity < 0)
	{
			if (ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.0f, newpos.y + 0.0f)) || ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.9f, newpos.y + 0.0f)))
			{
				newpos.y = (int)newpos.y + 1;
			}
	}
	else
	{
		if (ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.0f, newpos.y + 1.0f)) || ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.9f, newpos.y + 1.0f)))
		{
			newpos.y = (int)newpos.y;
			enemy->gravity = 0;
			enemy->is_on_ground = true;
		}
		else
			enemy->is_on_ground = false;
	}
		if (game->player.hit_block && (((int)game->player.hit.x == (int)newpos.x && (int)game->player.hit.y == (int)newpos.y + 1) ||
		((int)game->player.hit.x == (int)(newpos.x + 0.9)&& (int)game->player.hit.y == (int)newpos.y + 1)))
		{
			enemy->pos.y += 1.5;
			enemy->outofgame = true;
			enemy->collision = false;
		}
		if (game->multiplayer && game->player2.hit_block && (((int)game->player2.hit.x == (int)newpos.x && (int)game->player2.hit.y == (int)newpos.y + 1) ||
		((int)game->player2.hit.x == (int)(newpos.x + 0.9)&& (int)game->player2.hit.y == (int)newpos.y + 1)))
		{
				enemy->stopped = true;
				enemy->pos.y += 1.5;
				enemy->outofgame = true;
				enemy->collision = false;
		}
		enemy->pos.x = newpos.x;
		enemy->pos.y = newpos.y;
	}
