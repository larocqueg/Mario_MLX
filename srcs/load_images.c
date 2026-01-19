/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:25:34 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/08 18:36:19 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"


void get_textures(t_game *game)
{

	(*game).background.img = mlx_new_image((*game).mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	(*game).background.addr = mlx_get_data_addr((*game).background.img, &(*game).background.bits_per_pixel, &(*game).background.line_length, &(*game).background.endian);
	drawrect(&game->background, (t_point){0, 0}, (t_point){SCREEN_SIZE_X, SCREEN_SIZE_Y}, 0x5c94fc);

	(*game).image.img = mlx_new_image((*game).mlx_ptr, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	(*game).image.addr = mlx_get_data_addr((*game).image.img, &(*game).image.bits_per_pixel, &(*game).image.line_length, &(*game).image.endian);

	ft_load_images(game, &game->player.idle.frames[0], "./assets/idle.xpm");
	ft_load_images(game, &game->player.climbing.frames[0], "./assets/climb1.xpm");
	ft_load_images(game, &game->player.climbing.frames[1], "./assets/climb2.xpm");
	ft_load_images(game, &game->player2.climbing.frames[0], "./assets/climb1_luigi.xpm");
	ft_load_images(game, &game->player2.climbing.frames[1], "./assets/climb2_luigi.xpm");
	ft_load_images(game, &game->player.stopping.frames[0], "./assets/stopping.xpm");
	ft_load_images(game, &game->player.walking.frames[0], "./assets/walking.xpm");
	ft_load_images(game, &game->player.walking.frames[1], "./assets/walking1.xpm");
	ft_load_images(game, &game->player.walking.frames[2], "./assets/walking2.xpm");
	ft_load_images(game, &game->player.jumping.frames[0], "./assets/jumping.xpm");
	ft_load_images(game, &game->player.death.frames[0], "./assets/death.xpm");
	ft_load_images(game, &game->player2.idle.frames[0], "./assets/idle2.xpm");
	ft_load_images(game, &game->player2.stopping.frames[0], "./assets/stopping2.xpm");
	ft_load_images(game, &game->player2.walking.frames[0], "./assets/walkingl.xpm");
	ft_load_images(game, &game->player2.walking.frames[1], "./assets/walkingl1.xpm");
	ft_load_images(game, &game->player2.walking.frames[2], "./assets/walkingl2.xpm");
	ft_load_images(game, &game->player2.jumping.frames[0], "./assets/jumping2.xpm");
	ft_load_images(game, &game->player2.death.frames[0], "./assets/death2.xpm");
	ft_load_images(game, &game->ground, "./assets/ground.xpm");
	ft_load_images(game, &game->brick, "./assets/brick.xpm");
	ft_load_images(game, &game->stairs, "./assets/stair.xpm");
	ft_load_images(game, &game->pipe[LEFT], "./assets/pipeleft.xpm");
	ft_load_images(game, &game->pipe[RIGHT], "./assets/piperight.xpm");
	ft_load_images(game, &game->pipe[TOPLEFT], "./assets/pipetopleft.xpm");
	ft_load_images(game, &game->pipe[TOPRIGHT], "./assets/pipetopright.xpm");
	ft_load_images(game, &game->cloud[0], "./assets/nuvemsolo.xpm");
	ft_load_images(game, &game->cloud[1], "./assets/nuvemdupla.xpm");
	ft_load_images(game, &game->cloud[2], "./assets/nuvemtripla.xpm");
	ft_load_images(game, &game->grass[0], "./assets/gramasolo.xpm");
	ft_load_images(game, &game->grass[1], "./assets/gramadupla.xpm");
	ft_load_images(game, &game->grass[2], "./assets/gramatripla.xpm");
	ft_load_images(game, &game->goomba[0], "./assets/goomba1.xpm");
	ft_load_images(game, &game->goomba[1], "./assets/goomba2.xpm");
	ft_load_images(game, &game->goomba[2], "./assets/goomba3.xpm");
	ft_load_images(game, &game->hill, "./assets/morro.xpm");
	ft_load_images(game, &game->castle, "./assets/castle.xpm");
	ft_load_images(game, &game->little_hill, "./assets/morrinho.xpm");
	ft_load_images(game, &game->title_screen, "./assets/title_screen.xpm");
	ft_load_images(game, &game->selector, "./assets/selector.xpm");
	ft_load_images(game, &game->powerup[0], "./assets/powerup0.xpm");
	ft_load_images(game, &game->powerup[1], "./assets/powerup1.xpm");
	ft_load_images(game, &game->powerup[2], "./assets/powerup2.xpm");

	if (!ft_load_images(game, &game->flag, "./assets/flag.xpm"))
	{
		perror("failed to load flag\n");
	}
}
int	ft_load_images(t_game *game, t_image *image, char *name)
{
	image->img = mlx_xpm_file_to_image(game->mlx_ptr, \
			name, &image->x, &image->y);
	if (!image->img)
		return (0);
	image->addr = mlx_get_data_addr(image->img, \
			&image->bits_per_pixel, &image->line_length, \
			&image->endian);
	return (1);
}

void	ft_free_images(t_game *game, t_image *image)
{
	if (image->img)
		mlx_destroy_image(game->mlx_ptr, image->img);
}
