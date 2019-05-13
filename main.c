/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:27:59 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/13 06:39:06 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraminos.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static char			*x_init(unsigned short *ttrs, int square)
{
	t_dlist		**matrix;
	t_dlist		**rm;
	char		*result;
	char		*b;

	matrix = (t_dlist **)matrix_init(ttrs, square);
	result = (char *)malloc(square * square);
	ft_memset(result, '.', square * square);
	b = x_do_it(matrix, *matrix, result);
	rm = matrix;
	while (1)
		if (*rm++ == 0)
			continue ;
		else if ((*(rm - 1))->content)
			break ;
		else
			ft_dlstdel((rm - 1), (size_t)-1);
	if (*rm != 0)
		ft_dlstdel(rm, (size_t)-1);
	free(matrix);
	if (!b)
		ft_strdel(&result);
	return (result);
}

static void			solver(unsigned short *ttrs)
{
	const int	size = ttrs_size(ttrs);
	int			square;
	int			row;
	char		*result;

	square = sqrt_ceil(size * 4, ttrs);
	while (!(result = x_init(ttrs, square)))
	{
		free(result);
		square++;
	}
	row = 0;
	while (row < square)
	{
		write(1, &(result[row * square]), square);
		write(1, "\n", 1);
		row++;
	}
	ft_strdel(&result);
}

int					main(int argc, char const *argv[])
{
	unsigned short	tetrominos[MAX_TETROMINOS + 1];
	int				fd;

	if (argc < 2)
		invalid_tetr_handler();
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		invalid_tetr_handler();
	ttrs_input(fd, tetrominos);
	solver(tetrominos);
	return (0);
}
