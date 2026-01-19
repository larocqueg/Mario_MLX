/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:00:38 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/09 00:28:19 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	drawrect(t_image *image, t_point pos, t_point size, int color)
{
	int	x = 0;
	int y = 0;

	while (x < size.x)
	{
		y = 0;
		while (y < size.y)
		{
			ft_pixelput(image, pos.x + x, pos.y + y++, color);
		}
		x++;
	}
}

void	drawtexture(t_game *game, t_point pos, t_image *text, float scale)
{
	int	x = 0;
	int y = 0;
	unsigned int	color;
	t_point step = (t_point){0, 0};
	t_point texture;

	texture.x = 0;
	texture.y = 0;
	while (x < text->x * scale)
	{
		y = 0;
		while (y < text->y * scale)
		{
			texture.x = x / scale;
			texture.y = y / scale;

			if (texture.x < 0 || texture.x > text->x || texture.y < 0 || texture.y > text->y)
			{
				y++;
				continue;
			}
			color = *(int *)((*text).addr + ((int)texture.y * (*text).line_length + (int)texture.x * ((*text).bits_per_pixel / 8)));
			if (color == 0xFF000000)
			{
				y++;
				continue;
			}
			ft_pixelput(&game->image, pos.x + x, pos.y + y++, color);
		}
		texture.x += step.x;
		x++;
	}
}

void	drawplayer(t_game *game, t_point pos, t_image *text, float scale, bool left, bool flip)
{
	int	x = 0;
	int y = 0;
	unsigned int	color;
	t_point step = (t_point){0, 0};
	t_point texture;

	texture.x = 0;
	texture.y = 0;
	while (x < text->x * scale)
	{
		y = 0;
		while (y < text->y * scale)
		{
			if (left)
				texture.x = (text->x) - (x / scale);
			else
				texture.x = x / scale;
			if (flip)
				texture.y = (text->y -1) - (y / scale);
			else
				texture.y = y / scale;
			if (texture.x < 0 || texture.x >= text->x || texture.y < 0 || texture.y > text->y)
			{
				y++;
				continue;
			}
			color = *(int *)((*text).addr + ((int)texture.y * (*text).line_length + (int)texture.x * ((*text).bits_per_pixel / 8)));
			if (color == 0xFF000000)
			{
				y++;
				continue;
			}
			ft_pixelput(&game->image, pos.x + x, pos.y + y++, color);
		}

		texture.x += step.x;
		x++;
	}
}
