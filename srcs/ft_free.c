/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:39:30 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/06/04 18:08:00 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

/**/



void	ft_free(t_game *game, char *line)
{
	int	i;

	if (line)
		free(line);
	i = 0;
	if (game && game->map)
	{
		while (game->map[i])
			free(game->map[i++]);
		free(game->map);
	}
}

void	ft_free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return ;
}
