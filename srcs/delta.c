/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:01:43 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/04 18:08:00 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

void	calculate_Delta(t_game *game)
{
	long long	now;

	now = get_time();
	game->delta = (float)(now - game->last_frame_time) / 1000000.0f;
	if (game->delta > 0.05f)
		game->delta = 0.05f;
	if (game->delta < 0.0f)
		game->delta = 0.0f;
	game->last_frame_time = now;
}
