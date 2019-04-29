/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:27:59 by hgranule          #+#    #+#             */
/*   Updated: 2019/04/29 10:19:28 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraminos.h"
#include <fcntl.h>

static void	print_the_map(char map[MS][MS + 1])
{
	int		i;

	i = -1;
	while (++i < 16)
		ft_putendl(map[i]);
}

int			main(int argc, char const *argv[])
{
	unsigned short	tetrominos[MAX_TETROMINOS + 1];
	char			map[MAX_SQUARE][MAX_SQUARE + 1] =
	{
		"................",
		"................",
		"................",
		"................",
		"................",
		"................",
		"................",
		"................",
		"................",
		"................",
		"................",
		"................",
		"................",
		"................",
		"................",
		"................"
	};
	int				fd;
	int				xy[] = {1, 1};

	if (argc < 2)
		invalid_tetr_handler();
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		invalid_tetr_handler();
	ttrs_input(fd , tetrominos);
	draw_tmap(map, TETR_L_1, xy, 'A');
	xy[0] += 1;
	if (try_pos(map, TETR_S_V, xy))
		draw_tmap(map, TETR_S_V, xy, 'B');
	xy[0] += 1;
	if (try_pos(map, TETR_L_3, xy))
		draw_tmap(map, TETR_L_3, xy, 'C');
	print_the_map(map);
	return (0);
}
