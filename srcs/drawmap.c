/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 19:32:57 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/09 00:37:09 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"
void	draw_enemies(t_game *game, float offsetX);

void	drawmap(t_game *game)
{
	float	drawx;
	float	startingx;
	float 	endingx;
	char	c;
	float	mapx;
	float	cameraX;
	static float minoffsetx;
	float		hit_offset = 0;
	float		hit2_offset = 0;

	if (game->multiplayer && game->player.animation_state != DEATH && game->player2.animation_state != DEATH)
		cameraX = (game->player.pos.x + game->player2.pos.x) / 2;
	else if (game->player.animation_state != DEATH)
		cameraX = (game->player.pos.x);
	else if (game->multiplayer)
		cameraX = (game->player2.pos.x);
	else
		cameraX = (game->player.pos.x);
	float	tilesX = (float)SCREEN_SIZE_X / ((float)TILE_SIZE * SCALE);
	float	offsetX = cameraX - (tilesX / 2.0f );
	if (!SIDESCROLL)
		minoffsetx = 0;
	else if (offsetX > minoffsetx)
		minoffsetx = offsetX;
	offsetX = clamp(offsetX, minoffsetx, game->map_width - tilesX);
	game->cameraX = offsetX;
	float tileoffset = (offsetX - (int)offsetX) * (TILE_SIZE * SCALE);
	for (int y = 0; y < 15; y++)
	{
		for (int x = -5; x <= tilesX + 1; x++)
		{
			mapx = clamp(x + (int)offsetX, 0, game->map_width - 1);
			drawx = x * (TILE_SIZE * SCALE) - (tileoffset);
			if (mapx + offsetX < 0)
			{
				continue;
			}
			if (game->player.hit_block)
			{
				if (mapx == (int)game->player.hit.x && y == (int)game->player.hit.y)
					hit_offset = -0.3;
				else
					hit_offset = 0;
				game->player.hit_cooldown += game->delta;
				if (game->player.hit_cooldown > 75)
				{
					game->player.hit_block = false;

					if (!game->player2.hit_block)
					{
						hit_offset = 0;
						game->player.hit_cooldown = 0;
					}
				}
			}
			if (game->multiplayer && game->player2.hit_block)
			{
				if (mapx == (int)game->player2.hit.x && y == (int)game->player2.hit.y)
					hit_offset = -0.3;
				else
					hit_offset = 0;
				game->player2.hit_cooldown += game->delta;
				if (game->player2.hit_cooldown > 75)
				{
					game->player2.hit_block = false;

					if (!game->player.hit_block)
					{
						game->player2.hit_cooldown = 0;
						hit_offset = 0;
					}
				}
			}
			c = game->map[y][(int)mapx];
			if (c == '1')
				drawtexture(game, (t_point){drawx , y * (TILE_SIZE * SCALE)}, &game->ground, SCALE);
			else if (c == 'B')
				drawtexture(game, (t_point){drawx , (y + hit_offset) * ((TILE_SIZE ) * SCALE)}, &game->brick, SCALE);
			else if (c == 'Z')
				drawtexture(game, (t_point){drawx , y * (TILE_SIZE * SCALE)}, &game->stairs, SCALE);
			else if (c == 'K')
				drawtexture(game, (t_point){drawx , y * (TILE_SIZE * SCALE)}, &game->pipe[LEFT], SCALE);
			else if (c == 'L')
				drawtexture(game, (t_point){drawx , y * (TILE_SIZE * SCALE)}, &game->pipe[RIGHT], SCALE);
			else if (c == 'I')
				drawtexture(game, (t_point){drawx , y * (TILE_SIZE * SCALE)}, &game->pipe[TOPLEFT], SCALE);
			else if (c == 'O')
				drawtexture(game, (t_point){drawx , y * (TILE_SIZE * SCALE)}, &game->pipe[TOPRIGHT], SCALE);
			else if (c == 'T')
				drawtexture(game, (t_point){drawx , y * (TILE_SIZE * SCALE)}, &game->cloud[2], SCALE);
			else if (c == 'D')
				drawtexture(game, (t_point){drawx , y * (TILE_SIZE * SCALE)}, &game->cloud[1], SCALE);
			else if (c == 'S')
				drawtexture(game, (t_point){drawx , y * (TILE_SIZE * SCALE)}, &game->cloud[0], SCALE);
			else if (c == 'X')
				drawtexture(game, (t_point){drawx  , y * ((TILE_SIZE + 1.3) * SCALE)}, &game->hill, SCALE);
			else if (c == 'H')
				drawtexture(game, (t_point){drawx , y * ((TILE_SIZE + 1.3) * SCALE)}, &game->little_hill, SCALE);
			else if (c == 'V')
				drawtexture(game, (t_point){drawx , y * (TILE_SIZE * SCALE) }, &game->grass[0], SCALE);
			else if (c == 'N')
				drawtexture(game, (t_point){drawx , y * (TILE_SIZE * SCALE) }, &game->grass[1], SCALE);
			else if (c == 'J')
				drawtexture(game, (t_point){drawx , y * (TILE_SIZE * SCALE) }, &game->grass[2], SCALE);
			else if (c == 'C')
				drawtexture(game, (t_point){drawx , (y - 1) * ((TILE_SIZE) * SCALE) }, &game->castle, SCALE);
			else if (c == 'P')
				drawtexture(game, (t_point){drawx , (y + hit_offset) * ((TILE_SIZE) * SCALE)}, &game->powerup[game->power_up_frames], SCALE);
			else if (c == 'F')
				drawtexture(game, (t_point){drawx - TILE_SIZE , y * ((TILE_SIZE - 12.35) * SCALE)}, &game->flag, SCALE);

		}
	}

	draw_enemies(game, offsetX);
	if (game->player.animation_state == IDLE)
	{
		game->player.current_frame = 0;
		drawplayer(game, (t_point){(game->player.pos.x - offsetX) * (TILE_SIZE * SCALE), game->player.pos.y * (TILE_SIZE * SCALE)}, &game->player.idle.frames[0], SCALE, game->player.left, false);
	}
	else if (game->player.animation_state == WALKING)
	{
		animation_player(game, &game->player.walking, LOOP);
		drawplayer(game, (t_point){(game->player.pos.x - offsetX) * (TILE_SIZE * SCALE), game->player.pos.y * (TILE_SIZE * SCALE)}, &game->player.walking.frames[game->player.current_frame % 3], SCALE, game->player.left, false);
	}
	else if (game->player.animation_state == CLIMBING)
	{
		animation_player(game, &game->player.climbing, LOOP);
		drawplayer(game, (t_point){(game->player.pos.x - offsetX) * (TILE_SIZE * SCALE), game->player.pos.y * (TILE_SIZE * SCALE)}, &game->player.climbing.frames[game->player.current_frame % 2], SCALE, game->player.left, false);
	}
	else if (game->player.animation_state == JUMPING)
	{
		game->player.current_frame = 0;
		drawplayer(game, (t_point){(game->player.pos.x - offsetX) * (TILE_SIZE * SCALE), game->player.pos.y * (TILE_SIZE * SCALE)}, &game->player.jumping.frames[0], SCALE, game->player.left, false);
	}
	else if (game->player.animation_state == STOPPING)
	{
		game->player.current_frame = 0;
		drawplayer(game, (t_point){(game->player.pos.x - offsetX) * (TILE_SIZE * SCALE), game->player.pos.y * (TILE_SIZE * SCALE)}, &game->player.stopping.frames[0], SCALE, game->player.left, false);
	}
	else if (game->player.animation_state == DEATH)
	{
		game->player.current_frame = 0;
		drawplayer(game, (t_point){(game->player.pos.x - offsetX) * (TILE_SIZE * SCALE), game->player.pos.y * (TILE_SIZE * SCALE)}, &game->player.death.frames[0], SCALE, game->player.left, false);
		//need to stop game after this!!!!
	}
	if (!game->multiplayer)
		return ;
	if (game->player2.animation_state == IDLE)
	{
		game->player2.current_frame = 0;
		drawplayer(game, (t_point){(game->player2.pos.x - offsetX) * (TILE_SIZE * SCALE), game->player2.pos.y * (TILE_SIZE * SCALE)}, &game->player2.idle.frames[0], SCALE, game->player2.left, false);
	}
	else if (game->player2.animation_state == WALKING)
	{
		animation_player2(game, &game->player2.walking, LOOP);
		drawplayer(game, (t_point){(game->player2.pos.x - offsetX) * (TILE_SIZE * SCALE), game->player2.pos.y * (TILE_SIZE * SCALE)}, &game->player2.walking.frames[game->player2.current_frame % 3], SCALE, game->player2.left, false);
	}
	else if (game->player2.animation_state == CLIMBING)
	{
		animation_player2(game, &game->player2.climbing, LOOP);
		drawplayer(game, (t_point){(game->player2.pos.x - offsetX) * (TILE_SIZE * SCALE), game->player2.pos.y * (TILE_SIZE * SCALE)}, &game->player2.climbing.frames[game->player2.current_frame % 2], SCALE, game->player2.left, false);
	}
	else if (game->player2.animation_state == JUMPING)
	{
		game->player2.current_frame = 0;
		drawplayer(game, (t_point){(game->player2.pos.x - offsetX) * (TILE_SIZE * SCALE), game->player2.pos.y * (TILE_SIZE * SCALE)}, &game->player2.jumping.frames[0], SCALE, game->player2.left, false);
	}
	else if (game->player2.animation_state == STOPPING)
	{
		game->player2.current_frame = 0;
		drawplayer(game, (t_point){(game->player2.pos.x - offsetX) * (TILE_SIZE * SCALE), game->player2.pos.y * (TILE_SIZE * SCALE)}, &game->player2.stopping.frames[0], SCALE, game->player2.left, false);
	}
	else if (game->player2.animation_state == DEATH)
	{
		game->player2.current_frame = 0;
		drawplayer(game, (t_point){(game->player2.pos.x - offsetX) * (TILE_SIZE * SCALE), game->player2.pos.y * (TILE_SIZE * SCALE)}, &game->player2.death.frames[0], SCALE, game->player2.left, false);
		//need to stop game after this!!!!
	}
}

void	draw_enemies(t_game *game, float offsetX)
{
	int frames = 0;
	for (int i = 0; i <= game->goomba_count; i++)
	{
		if (!game->goombas[i].exist)
			continue;
		if (game->goombas[i].pos.y < 16 && game->goombas[i].pos.x >= game->cameraX - TILE_SIZE && game->goombas[i].pos.x - game->cameraX < 30)
		{
			frames = game->power_up_frames % 2;
			if (game->goombas[i].stopped)
				frames = 2;
			drawplayer(game, (t_point){(game->goombas[i].pos.x - offsetX) * (TILE_SIZE * SCALE), game->goombas[i].pos.y * (TILE_SIZE * SCALE)}, &game->goomba[frames], SCALE, game->goombas[i].left, game->goombas[i].outofgame);

		}
	}
}
