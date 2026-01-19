/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:49:29 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/06 18:58:08 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	animation_times(t_game *game)
{
	static float accumulator;
	accumulator += game->delta;

	if (accumulator > 0.25)
	{
		game->power_up_frames++;
		if (game->power_up_frames > 2)
			game->power_up_frames = 0;
		accumulator = 0;
	}

}

void	animation_player(t_game *game, t_frames *anim, int type)
{
	static float accumulator;
	float		time;
	float		mintime;
	float		maxtime;


	if (!game->player.running)
	{
		mintime = 0.08;
	}
	else
	{
		mintime = 0.05;
	}
	time = ((10 - fabs(game->player.velocity.x)) * 1.5) / 100;
	time = clamp(time + mintime, mintime, 0.17);
	if (type == LOOP)
	{
		accumulator += game->delta;

		if (accumulator > time)
		{
			game->player.current_frame++;
			accumulator = 0;
		}
	}
}
void	animation_player2(t_game *game, t_frames *anim, int type)
{
	static float accumulator;
	float		time;
	float		mintime;
	float		maxtime;


	if (!game->player2.running)
	{
		mintime = 0.08;
	}
	else
	{
		mintime = 0.05;
	}
	time = ((10 - fabs(game->player2.velocity.x)) * 1.5) / 100;
	time = clamp(time + mintime, mintime, 0.17);
	if (type == LOOP)
	{
		accumulator += game->delta;

		if (accumulator > time)
		{
			game->player2.current_frame++;
			accumulator = 0;
		}
	}
}
