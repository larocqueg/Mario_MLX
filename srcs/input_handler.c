/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:09:07 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/08 18:44:48 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	key_pressed(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		free_displays(game);
	
	if (!game->ended_p1)
	{
		if (keysym == XK_w || keysym == XK_W)
		{
			game->player.direction.y -= 1;
			game->player.direction.y = clamp(game->player.direction.y, -1, 1);
		}
		if (keysym == XK_s || keysym == XK_S)
		{
			game->player.direction.y += 1;
			game->player.direction.y = clamp(game->player.direction.y, -1, 1);
		}
		if (keysym == XK_A || keysym == XK_a)
		{
			game->player.direction.x -= 1;
			game->player.direction.x = clamp(game->player.direction.x, -1, 1);
		}
		if (keysym == XK_d || keysym == XK_D)
		{
			game->player.direction.x += 1;
			game->player.direction.x = clamp(game->player.direction.x, -1, 1);
		}
		if (keysym == XK_space)
		{
			game->player.holding = true;
			if (!game->player.is_on_ground)
				return 1;
			game->player.jump = true;
		}
		if (keysym == XK_Shift_L)
		{
			game->player.running = true;
		}
	}
	if (game->ended_p2)
		return (1);
	if (keysym == XK_Up)
	{
		game->player2.direction.y -= 1;
		game->player2.direction.y = clamp(game->player2.direction.y, -1, 1);
	}
	if (keysym == XK_Down)
	{
		game->player2.direction.y += 1;
		game->player2.direction.y = clamp(game->player2.direction.y, -1, 1);
	}
	if (keysym ==XK_Left)
	{
		game->player2.direction.x -= 1;
		game->player2.direction.x = clamp(game->player2.direction.x, -1, 1);
	}
	if (keysym == XK_Right)
	{
		game->player2.direction.x += 1;
		game->player2.direction.x = clamp(game->player2.direction.x, -1, 1);
	}
	if (keysym == 65438)
	{
		game->player2.holding = true;
		if (!game->player2.is_on_ground)
			return 1;
		game->player2.jump = true;
	}
	if (keysym == XK_Control_R)
	{
		game->player2.running = true;
	}
	return (1);
}

int	key_released(int keysym, t_game *game)
{

	if (keysym == XK_w || keysym == XK_W)
	{
		game->player.direction.y += 1;
		game->player.direction.y = clamp(game->player.direction.y, -1, 1);
		if (!game->started)
		{
			if (game->multiplayer)
			{
				game->multiplayer = false;
			}
			else
				game->multiplayer = true;
		}
	}
	if (keysym == XK_s || keysym == XK_S)
	{
		game->player.direction.y -= 1;
		game->player.direction.y = clamp(game->player.direction.y, -1, 1);
		if (!game->started)
		{
			if (game->multiplayer)
			{
				game->multiplayer = false;
			}
			else
				game->multiplayer = true;
		}
	}
	if (keysym == XK_A || keysym == XK_a)
	{
		game->player.direction.x += 1;
		game->player.direction.x = clamp(game->player.direction.x, -1, 1);
		if (!game->started)
		{
			if (game->multiplayer)
			{
				game->multiplayer = false;
			}
			else
				game->multiplayer = true;
		}
	}
	if (keysym == XK_d || keysym == XK_D)
	{
		game->player.direction.x -= 1;
		game->player.direction.x = clamp(game->player.direction.x, -1, 1);
		if (!game->started)
		{
			if (game->multiplayer)
			{
				game->multiplayer = false;
			}
			else
				game->multiplayer = true;
		}
	}
	if (keysym == XK_Shift_L)
	{
		game->player.running = false;
	}
	if (keysym == XK_space)
	{
		game->player.holding = false;
		if (!game->started)
			game->started = true;
	}
		if (keysym == XK_Up)
	{
		game->player2.direction.y = clamp(game->player2.direction.y + 1, -1, 1);

	}
	if (keysym == XK_Down)
	{
		game->player2.direction.y = clamp(game->player2.direction.y - 1, -1, 1);
	}
	if (keysym ==XK_Left)
	{
		game->player2.direction.x = clamp(game->player2.direction.x + 1, -1, 1);
	}
	if (keysym == XK_Right)
	{
		game->player2.direction.x = clamp(game->player2.direction.x - 1, -1, 1);
	}
	if (keysym == 65438)
	{
		game->player2.holding = false;

	}
	if (keysym == XK_Control_R)
	{
		game->player2.running = false;
	}
	return (1);
}
