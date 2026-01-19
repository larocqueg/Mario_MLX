#include "../includes/game.h"

float 	move_towards(float start, float goal, float step);
void	move_enemies(t_game *game);
bool 	is_colliding(t_point posA, t_point sizeA, t_point posB, t_point sizeB);
void	enemy_collision(t_game *game, t_enemy *enemy, t_point newpos);


char	get_tile(t_game *game, int x, int y);

void	move_player_2(t_game *game)
{
float accel;
	float max_speed;
	static float accumulator;
	float	old_pos_y = game->player2.pos.y;
	char c;
	if (game->player2.running)
	{
		accel = RUNNING_ACCEL;
		max_speed = MAX_RUNNING_SPEED;
	}
	else
	{
		accel = ACCEL;
		max_speed = MAX_SPEED;
	}
	if (game->player2.direction.x > 0)
		game->player2.left = false;
	else if (game->player2.direction.x < 0)
		game->player2.left = true;
	if (game->ended_p2 && game->player2.pos.x < game->castle_pos && game->player2.is_on_ground)
	{
		game->player2.velocity.x = 5;
		game->player2.animation_state = WALKING;
	}
	if (!game->player2.is_on_ground)
	{
		if ((!game->player2.holding || accumulator > 0.3 || game->player2.animation_state == DEATH))
		{
			if (!game->ended_p2)
				game->player2.velocity.y += GRAVITY * game->delta;
			else
			{
				game->player2.velocity.y = 6;
			}
			if (game->player2.animation_state != DEATH)
				game->player2.animation_state = JUMPING;
			else
			{
				game->player2.pos.y += game->player2.velocity.y * game->delta;
				return ;
			}
			game->player2.holding = false;
			game->player2.falling = true;
			if (game->ended_p2)
			{
				game->player2.animation_state = CLIMBING;
			}
		}
		else
			accumulator += game->delta;
	}
	else
	{
		game->player2.velocity.y = 0;
	}
	if (game->player2.jump && game->player2.is_on_ground && !game->ended_p2)
	{
		accumulator = 0;
		game->player2.is_on_ground = false;
		game->player2.velocity.y = -JUMP_SPEED;
		game->player2.jump = false;
		if (game->player2.animation_state != DEATH)
			game->player2.animation_state = JUMPING;
	}
	if (game->player2.direction.x != 0 && !game->ended_p2)
	{
		if (game->player2.velocity.y == 0 && game->player2.velocity.x != 0)
		{
			game->player2.animation_state = WALKING;
			if ((game->player2.velocity.x > 0 && game->player2.direction.x < 0) ||
				(game->player2.velocity.x < 0 && game->player2.direction.x > 0 ))
			{
				game->player2.animation_state = STOPPING;
			}
		}
		game->player2.velocity.x += game->player2.direction.x * accel * game->delta;
		game->player2.velocity.x = clamp(game->player2.velocity.x, -max_speed, max_speed);
	}
	else if (fabs(game->player2.velocity.x) > 0)
	{
		if (game->player2.velocity.x > 0)
			game->player2.velocity.x = move_towards(game->player2.velocity.x, 0, FRICTION * game->delta);
		else if (game->player2.velocity.x < 0)
			game->player2.velocity.x = move_towards(game->player2.velocity.x, 0, FRICTION * game->delta);
	}
	else
	{
		game->player2.velocity.x = 0;
		if (game->player2.velocity.y == 0 && game->player2.velocity.x == 0)
			game->player2.animation_state = IDLE;
	}

	t_point newpos;
	newpos.x = game->player2.pos.x + game->player2.velocity.x * game->delta;
	newpos.y = game->player2.pos.y + game->player2.velocity.y * game->delta;

	if (game->player2.velocity.x <= 0)
	{
		if (game->player2.pos.x <= game->cameraX)
		{
			game->player2.pos.x = game->cameraX + 0.1;
			game->player2.velocity.x = 0;
			if (game->player2.velocity.y == 0)
				game->player2.animation_state = IDLE;
		}
		if (ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.0f, game->player2.pos.y + 0.0f)) || ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.0f, game->player2.pos.y + 0.9f)))
		{
			newpos.x = (int)newpos.x + 1;
			game->player2.velocity.x = 0;
		}

	}
	else
	{
		if (game->player2.pos.x >= game->cameraX + 25.7)
		{
			game->player2.pos.x = game->cameraX + 25.7;
			game->player2.velocity.x = 0;
			if (game->player2.velocity.y == 0)
				game->player2.animation_state = IDLE;
		}
		if (ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 1.0f, game->player2.pos.y + 0.0f)) || ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 1.0f, game->player2.pos.y + 0.9)))
		{

			newpos.x = (int)newpos.x;
			game->player2.velocity.x = 0;

		}
		if (newpos.x >= game->flag_pos - 0.5)
		{
			game->player2.velocity.x = 0;
			game->player2.velocity.y = 1;
			game->ended_p2 = true;
		}
	}
	if (game->player2.velocity.y < 0)
	{
			if (ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.0f, newpos.y + 0.0f)) || ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.9f, newpos.y + 0.0f)))
			{
				if (ft_strchr("BP",  get_tile(game, newpos.x + 0.0f, newpos.y + 0.0f)))
				{
					game->player2.hit_block = true;
					game->player2.hit.x = newpos.x;
					game->player2.hit.y = newpos.y ;
					game->player2.hit_cooldown = 0;
				}
				else
				{
					game->player2.hit.x = -1;
					game->player2.hit.y = -1;
				}
				if (ft_strchr("BP",  get_tile(game, newpos.x + 0.5f, newpos.y + 0.0f)))
				{
					game->player2.hit_block = true;
					game->player2.hit.x = newpos.x + 0.5f;
					game->player2.hit.y = newpos.y;
					game->player2.hit_cooldown = 0;
				}
				else
				{
					game->player2.hit.x = -1;
					game->player2.hit.y = -1;
				}
				newpos.y = (int)newpos.y + 1;
				game->player2.velocity.y = 0;
				accumulator = 5;

			}
	}
	else
	{
			if (ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.0f, newpos.y + 1.0f)) || ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.9f, newpos.y + 1.0f)))
			{
				newpos.y = (int)newpos.y;
				game->player2.velocity.y = 0;
				game->player2.is_on_ground = true;
				game->player2.falling = false;
			}
			else
			{
				if ((int)newpos.y > 14)
				{
					if (game->player2.animation_state == DEATH)
						return ;
					game->player2.animation_state = DEATH;
					game->player2.is_on_ground = false;
					game->player2.velocity.y = -12;
					return ;
				}
				game->player2.is_on_ground = false;
			}
	}
		if (newpos.x == game->player2.pos.x && newpos.y == game->player2.pos.y && game->player2.animation_state == JUMPING)
			game->player2.animation_state = IDLE;
		game->player2.pos.x = newpos.x;
		game->player2.pos.y = newpos.y;
}


