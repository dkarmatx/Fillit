/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 04:33:20 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/16 19:12:08 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraminos.h"
#include <stdlib.h>

int			sqrt_ceil(int b, unsigned short *ttrs)
{
	int			a;
	int			sq_hack;

	sq_hack = 0;
	a = 2;
	while (*ttrs == TETR_O_1)
	{
		ttrs++;
		sq_hack++;
	}
	if (*ttrs == 0)
	{
		if (sq_hack > 4)
			a = 6;
		if (sq_hack > 9)
			a = 8;
		if (sq_hack > 16)
			a = 10;
		if (sq_hack > 24)
			a = 12;
	}
	else
		while (a * a < b)
			a++;
	return (a);
}

char		*str_gen(unsigned short ttr, char c, int square, int step)
{
	char		*str;
	int			i;
	int			j;
	int			row;

	i = 0;
	str = (char *)malloc_safe(square * square + 1);
	str[square * square] = 0;
	ft_memset(str, '.', square * square);
	while (i++ < 4)
	{
		j = -1;
		row = step / square;
		while (++j < 4)
			if ((ttr & (32768 >> j)))
				if (((step + j) < ((row + 1) * square) && row < square) \
				|| !(i = 5))
					str[step + j] = c;
		if (i == 5)
			ft_strdel(&str);
		ttr <<= 4;
		step += square;
	}
	return (str);
}

t_dlist		*matrix_gen(unsigned short ttr, char c, int square)
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
				matrix[0] = dlstnew_safe(str, square2 + 1);
			else
			{
				matrix[1] = dlstnew_safe(str, square2 + 1);
				ft_dlstunshift(&(matrix[0]), matrix[1]);
			}
			ft_strdel(&str);
		}
	}
	return (matrix[0]);
}

t_dlist		**matrix_init(unsigned short *ttrs, int square)
{
	const int		size = ttrs_size(ttrs);
	t_dlist			**matrix;
	int				i;
	char			c;

	matrix = (t_dlist **)malloc_safe(sizeof(t_dlist *) * (size + 1));
	i = 0;
	c = 'A';
	while (i < size)
	{
		matrix[i] = matrix_gen(ttrs[i], c++, square);
		i++;
	}
	matrix[size] = dlstnew_safe(0, 0);
	return (matrix);
}
