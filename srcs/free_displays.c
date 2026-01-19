/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_displays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:41:42 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/04 18:08:00 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	ft_freesplit(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free (str[i]);
		i++;
	}
	free(str);
}

void	ft_free_images(t_game *game, t_image *image);



void free_images(t_game *game)
{
	ft_free_images(game, &game->background);
	ft_free_images(game, &game->image);
	ft_free_images(game, &game->player.idle.frames[0]);
	ft_free_images(game, &game->player.climbing.frames[0]);
	ft_free_images(game, &game->player.climbing.frames[1]);
	ft_free_images(game, &game->player2.climbing.frames[0]);
	ft_free_images(game, &game->player2.climbing.frames[1]);
	ft_free_images(game, &game->player.stopping.frames[0]);
	ft_free_images(game, &game->player.walking.frames[0]);
	ft_free_images(game, &game->player.walking.frames[1]);
	ft_free_images(game, &game->player.walking.frames[2]);
	ft_free_images(game, &game->player.jumping.frames[0]);
	ft_free_images(game, &game->player.death.frames[0]);
	ft_free_images(game, &game->player2.idle.frames[0]);
	ft_free_images(game, &game->player2.stopping.frames[0]);
	ft_free_images(game, &game->player2.walking.frames[0]);
	ft_free_images(game, &game->player2.walking.frames[1]);
	ft_free_images(game, &game->player2.walking.frames[2]);
	ft_free_images(game, &game->player2.jumping.frames[0]);
	ft_free_images(game, &game->player2.death.frames[0]);
	ft_free_images(game, &game->ground);
	ft_free_images(game, &game->brick);
	ft_free_images(game, &game->stairs);
	ft_free_images(game, &game->pipe[LEFT]);
	ft_free_images(game, &game->pipe[RIGHT]);
	ft_free_images(game, &game->pipe[TOPLEFT]);
	ft_free_images(game, &game->pipe[TOPRIGHT]);
	ft_free_images(game, &game->cloud[0]);
	ft_free_images(game, &game->cloud[1]);
	ft_free_images(game, &game->cloud[2]);
	ft_free_images(game, &game->grass[0]);
	ft_free_images(game, &game->grass[1]);
	ft_free_images(game, &game->grass[2]);
	ft_free_images(game, &game->goomba[0]);
	ft_free_images(game, &game->goomba[1]);
	ft_free_images(game, &game->goomba[2]);
	ft_free_images(game, &game->hill);
	ft_free_images(game, &game->castle);
	ft_free_images(game, &game->little_hill);
	ft_free_images(game, &game->title_screen);
	ft_free_images(game, &game->selector);
	ft_free_images(game, &game->powerup[0]);
	ft_free_images(game, &game->powerup[1]);
	ft_free_images(game, &game->powerup[2]);
	ft_free_images(game, &game->flag);
}

int	free_displays(t_game *game)
{
	mlx_loop_end((*game).mlx_ptr);
	free_images(game);
	mlx_destroy_window((*game).mlx_ptr, (*game).win_ptr);
	mlx_destroy_display((*game).mlx_ptr);
	ft_freesplit((*game).map);

	free((*game).mlx_ptr);
	ft_printf("Closing Application!");
	exit(1);
	return (0);
}
