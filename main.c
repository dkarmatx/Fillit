/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:27:59 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/07 05:57:00 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraminos.h"
#include <fcntl.h>
#include <stdlib.h>

static int			sqrt_ceil(int b)
{
	int			a;

	a = 2;
	while (a * a < b)
		a++;
	return (a);
}

static char			*str_gen(unsigned short ttr, char c, int square, int step)
{
	char		*str;
	int			i;
	int			row;

	i = 0;
	row = step / square;
	str = (char *)malloc(square * square + 1);
	ft_memset(str, '.', square * square);
	while (i++ < 4)
	{
		if (ttr & 0b1000000000000000)
			if (row < square || (i = 0))
				str[step] = c;
		if (ttr & 0b0100000000000000)
			if (((step + 1) < ((row + 1) * square) && row < square) || (i = 0))
				str[step + 1] = c;
		if (ttr & 0b0010000000000000)
			if (((step + 2) < ((row + 1) * square) && row < square) || (i = 0))
				str[step + 2] = c;
		if (ttr & 0b0001000000000000)
			if (((step + 3) < ((row + 1) * square) && row < square) || (i = 0))
				str[step + 3] = c;
		if (!i)
			return (0);
		ttr <<= 4;
		step += square;
		row++;
	}
	str[square * square] = 0;
	return (str);
}

static t_dlist		*matrix_gen(unsigned short ttr, char c, int square)
{
	int				step;
	const size_t	square2 = square * square;
	t_dlist			*matrix[2];
	char			*str;

	matrix[0] = 0;
	step = square2;
	while (--step >= 0)
	{
		if ((str = str_gen(ttr, c, square, step)))
		{
			if (!matrix[0])
				matrix[0] = ft_dlstnew(str, square2 + 1);
			else
			{
				matrix[1] = ft_dlstnew(str, square2 + 1);
				ft_dlstunshift(&(matrix[0]), matrix[1]);
			}
			ft_strdel(&str);
		}
	}
	return (matrix[0]);
}

/*
** Создание массива матриц инцидентности для каждого элемента.
*/
static t_dlist		**matrix_init(unsigned short *ttrs, int square)
{
	const int		size = ttrs_size(ttrs);
	t_dlist			**matrix;
	int				i;
	char			c;

	matrix = (t_dlist **)malloc(sizeof(t_dlist *) * size);
	i = 0;
	c = 'A';
	while (i < size)
	{
		matrix[i] = matrix_gen(ttrs[i], c++, square);
		i++;
	}
	return (matrix);
}

/*
** Алгоритм Х возвращающий строку с решением.
*/
static char			*algorithm_x(unsigned short *ttrs, int square)
{
	const t_dlist	**matrix = matrix_init(ttrs, square);
}

/*
** Запуск Алгоритма Х для квадрата определнной длины.
*/
static void			solver(unsigned short *ttrs)
{
	const int	size = ttrs_size(ttrs);
	int			square;

	square = sqrt_ceil(size * 4);
	while (!algorithm_x(ttrs, square))
		square++;
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
