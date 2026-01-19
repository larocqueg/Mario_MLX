#include "../includes/game.h"

float move_towards(float start, float goal, float step);
void	move_enemies(t_game *game);
bool is_colliding(t_point posA, t_point sizeA, t_point posB, t_point sizeB);
void	enemy_collision(t_game *game, t_enemy *enemy, t_point newpos);


char	get_tile(t_game *game, int x, int y);

void	move(t_game *game)
{
	float accel;
	float max_speed;
	static float accumulator;
	float	old_pos_y = game->player.pos.y;
	char c;
	if (game->player.running)
	{
		accel = RUNNING_ACCEL;
		max_speed = MAX_RUNNING_SPEED;
	}
	else
	{
		accel = ACCEL;
		max_speed = MAX_SPEED;
	}
	if (game->player.direction.x > 0)
		game->player.left = false;
	else if (game->player.direction.x < 0)
		game->player.left = true;
	if (game->ended_p1 && game->player.pos.x < game->castle_pos && game->player.is_on_ground)
	{
		game->player.velocity.x = 5;
		game->player.animation_state = WALKING;
	}
	if (!game->player.is_on_ground)
	{
		if ((!game->player.holding || accumulator > 0.3 || game->player.animation_state == DEATH))
		{
			if (!game->ended_p1)
				game->player.velocity.y += GRAVITY * game->delta;
			else
			{
				game->player.velocity.y = 6;
			}
			if (game->player.animation_state != DEATH)
				game->player.animation_state = JUMPING;
			else
			{
				game->player.pos.y += game->player.velocity.y * game->delta;
				return ;
			}
			game->player.holding = false;
			game->player.falling = true;
			if (game->ended_p1)
			{
				game->player.animation_state = CLIMBING;
			}
		}
		else
			accumulator += game->delta;
	}
	else
	{
		game->player.velocity.y = 0;
	}
	if (game->player.jump && game->player.is_on_ground && !game->ended_p1)
	{
		accumulator = 0;
		game->player.is_on_ground = false;
		game->player.velocity.y = -JUMP_SPEED;
		game->player.jump = false;
		if (game->player.animation_state != DEATH)
			game->player.animation_state = JUMPING;
	}
	if (game->player.direction.x != 0 && !game->ended_p1)
	{
		if (game->player.velocity.y == 0 && game->player.velocity.x != 0)
		{
			game->player.animation_state = WALKING;
			if ((game->player.velocity.x > 0 && game->player.direction.x < 0) ||
				(game->player.velocity.x < 0 && game->player.direction.x > 0 ))
			{
				game->player.animation_state = STOPPING;
			}
		}
		game->player.velocity.x += game->player.direction.x * accel * game->delta;
		game->player.velocity.x = clamp(game->player.velocity.x, -max_speed, max_speed);
	}
	else if (fabs(game->player.velocity.x) > 0)
	{
		if (game->player.velocity.x > 0)
			game->player.velocity.x = move_towards(game->player.velocity.x, 0, FRICTION * game->delta);
		else if (game->player.velocity.x < 0)
			game->player.velocity.x = move_towards(game->player.velocity.x, 0, FRICTION * game->delta);
	}
	else
	{
		game->player.velocity.x = 0;
		if (game->player.velocity.y == 0 && game->player.velocity.x == 0)
			game->player.animation_state = IDLE;
	}

	t_point newpos;
	newpos.x = game->player.pos.x + game->player.velocity.x * game->delta;
	newpos.y = game->player.pos.y + game->player.velocity.y * game->delta;

	if (game->player.velocity.x <= 0)
	{
		if (game->player.pos.x <= game->cameraX)
		{
			game->player.pos.x = game->cameraX + 0.1;
			game->player.velocity.x = 0;
			if (game->player.velocity.y == 0)
				game->player.animation_state = IDLE;
		}
		if (ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.0f, game->player.pos.y + 0.0f)) || ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.0f, game->player.pos.y + 0.9f)))
		{
			newpos.x = (int)newpos.x + 1;
			game->player.velocity.x = 0;
		}

	}
	else
	{
		if (game->player.pos.x >= game->cameraX + 25.7)
		{
			game->player.pos.x = game->cameraX + 25.7;
			game->player.velocity.x = 0;
			if (game->player.velocity.y == 0)
				game->player.animation_state = IDLE;
		}
		if (ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 1.0f, game->player.pos.y + 0.0f)) || ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 1.0f, game->player.pos.y + 0.9)))
		{

			newpos.x = (int)newpos.x;
			game->player.velocity.x = 0;

		}
		if (newpos.x >= game->flag_pos - 0.5)
		{
			game->player.velocity.x = 0;
			game->player.velocity.y = 1;
			game->ended_p1 = true;
		}
	}
	if (game->player.velocity.y < 0)
	{
			if (ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.0f, newpos.y + 0.0f)) || ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.9f, newpos.y + 0.0f)))
			{
				if (ft_strchr("BP",  get_tile(game, newpos.x + 0.0f, newpos.y + 0.0f)))
				{
					game->player.hit_block = true;
					game->player.hit.x = newpos.x;
					game->player.hit.y = newpos.y ;
					game->player.hit_cooldown = 0;
				}
				else
				{
					game->player.hit.x = -1;
					game->player.hit.y = -1;
				}
				if (ft_strchr("BP",  get_tile(game, newpos.x + 0.5f, newpos.y + 0.0f)))
				{
					game->player.hit_block = true;
					game->player.hit.x = newpos.x + 0.5f;
					game->player.hit.y = newpos.y;
					game->player.hit_cooldown = 0;
				}
				else
				{
					game->player.hit.x = -1;
					game->player.hit.y = -1;
				}
				newpos.y = (int)newpos.y + 1;
				game->player.velocity.y = 0;
				accumulator = 5;

			}
	}
	else
	{
			if (ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.0f, newpos.y + 1.0f)) || ft_strchr("BP1IOKLZ", get_tile(game, newpos.x + 0.9f, newpos.y + 1.0f)))
			{
				newpos.y = (int)newpos.y;
				game->player.velocity.y = 0;
				game->player.is_on_ground = true;
				game->player.falling = false;
			}
			else
			{
				if ((int)newpos.y > 14)
				{
					if (game->player.animation_state == DEATH)
						return ;
					game->player.animation_state = DEATH;
					game->player.is_on_ground = false;
					game->player.velocity.y = -12;
					return ;
				}
				game->player.is_on_ground = false;
			}
	}
		if (newpos.x == game->player.pos.x && newpos.y == game->player.pos.y && game->player.animation_state == JUMPING)
			game->player.animation_state = IDLE;
		game->player.pos.x = newpos.x;
		game->player.pos.y = newpos.y;
}


char	get_tile(t_game *game, int x, int y)
{
	if (x >= 0 && x < game->map_width && y >= 0 && y < game->map_height)
	{
		return game->map[y][x];
	}
	else
		return '.';
}

float move_towards(float start, float goal, float step)
{
	if (start < goal)
		return (fminf(start + step, goal));
	else if (start > goal)
		return (fmaxf(start - step, goal));
	else
		return (start);
}

bool is_colliding(t_point posA, t_point sizeA, t_point posB, t_point sizeB)
{
	float leftA   = posA.x;
	float rightA  = posA.x + sizeA.x;
	float topA    = posA.y;
	float bottomA = posA.y + sizeA.y;

	float leftB   = posB.x;
	float rightB  = posB.x + sizeB.x;
	float topB    = posB.y;
	float bottomB = posB.y + sizeB.y;

	if (rightA <= leftB || leftA >= rightB || bottomA <= topB || topA >= bottomB)
		return false;

	return true;
}

void	move_enemies(t_game *game)
{
	t_point newpos;
	for (int i = 0; i <= game->goomba_count; i++)
	{
		if (game->player.animation_state == DEATH && game->player2.animation_state == DEATH)
			break ;
		if (game->goombas[i].stopped && game->goombas[i].exist)
		{
			game->goombas[i].despawn += game->delta;
			if (game->goombas[i].despawn > 0.2)
				game->goombas[i].exist = false;
			continue ;
		}

		if (!game->goombas[i].exist)
			continue ;
		if (game->goombas[i].pos.y > 16)
			continue;
		if ((game->goombas[i].pos.x - game->cameraX) < 27)
			game->goombas[i].started = true;
		if (game->goombas[i].started)
		{
			if (!game->goombas[i].outofgame && is_colliding(game->player.pos, (t_point){1, 1}, game->goombas[i].pos, (t_point){1, 1}) && game->player.animation_state != DEATH)
			{
				if (game->player.pos.y < game->goombas[i].pos.y - 0.1 && game->player.velocity.y > 0)
				{
					game->player.velocity.y = -7;
					game->goombas[i].stopped = true;
					continue ;
				}
				else if (game->player.pos.y >= game->goombas[i].pos.y - 0.1 && (game->player.pos.x >= game->goombas[i].pos.x) || (game->player.pos.x <= game->goombas[i].pos.x))
				{
					if (game->player.animation_state != DEATH)
					{
						game->player.animation_state = DEATH;
						game->player.is_on_ground = false;
						game->player.velocity.y = -12;
					}
				}
			}
			else if (!game->goombas[i].outofgame && is_colliding(game->player2.pos, (t_point){1, 1}, game->goombas[i].pos, (t_point){1, 1}) && game->player2.animation_state != DEATH)
			{
				if (game->player2.pos.y < game->goombas[i].pos.y - 0.1 && game->player2.velocity.y > 0)
				{
					game->player2.velocity.y = -7;
					game->goombas[i].stopped = true;
					continue ;
				}
				else if (game->player2.pos.y >= game->goombas[i].pos.y - 0.1 && (game->player2.pos.x >= game->goombas[i].pos.x) || (game->player2.pos.x <= game->goombas[i].pos.x))
				{
					if (game->player2.animation_state != DEATH)
					{
						game->player2.animation_state = DEATH;
						game->player2.is_on_ground = false;
						game->player2.velocity.y = -12;
					}
				}
			}
			newpos.x = game->goombas[i].pos.x + (ENEMY_SPEED * (game->goombas[i].direction.x) * game->delta);
			if (!game->goombas[i].is_on_ground || game->goombas[i].outofgame)
				game->goombas[i].gravity += GRAVITY * game->delta;
			else
				game->goombas[i].gravity = 0;
			newpos.y = game->goombas[i].pos.y + game->goombas[i].gravity * game->delta;
			enemy_collision(game, &game->goombas[i], newpos);
			if (game->goombas[i].direction.x >= 0)
				game->goombas[i].left = true;
			else
				game->goombas[i].left = false;


		}
	}
}
