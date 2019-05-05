/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:27:59 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/05 05:15:02 by hgranule         ###   ########.fr       */
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

/*
** Генерация матрицы для одного элемента, где с это символ зарисовки элемента.
** step_check должна проверить для данного шага, можно ли туда вставить тетромину.
** step_check вернет -1 то значит мы перебрали все варинаты (правый нижний угол).
** если вернет 0, значит мы дошли до правой границы и надо перескочить шаг на следущий "ряд"
** ПО задумке после матрикс_ген функции вернется матрица на двусвязном списке, где строки
** этой матрицы это все возможные позиции тетроминки на карте.
*/
static t_dlist		*matrix_gen(unsigned short ttr, char c, int square)
{
	int		step;
	int		res;

	step = 0;
	while (1)
	{
		if ((res = step_check(ttr, square)) == -1) //TODO Сделать функцию степчек, либо продумать перебор
			break;
		if (res == 0)
			step = ((step / square) * square) + 1;
		if (res == 1)
		{
			
		}
	}
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
		matrix[i] = matrix_gen(ttrs[i++], c++, square);
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
