/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:27:59 by hgranule          #+#    #+#             */
/*   Updated: 2019/04/29 07:42:07 by hgranule         ###   ########.fr       */
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
	print_the_map(map);
	return (0);
}
