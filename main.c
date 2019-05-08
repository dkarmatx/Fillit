/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:27:59 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/08 16:13:32 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraminos.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

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

	matrix = (t_dlist **)malloc(sizeof(t_dlist *) * (size + 1));
	i = 0;
	c = 'A';
	while (i < size)
	{
		matrix[i] = matrix_gen(ttrs[i], c++, square);
		i++;
	}
	matrix[size] = ft_dlstnew(0, 0);
	return (matrix);
}

static t_dlist		*spec_dlst_cut(t_dlist **cutdlst)
{
	const t_dlist		*clst = (*cutdlst);

	if (!cutdlst || !(*cutdlst))
		return (0);
	if (!((*cutdlst)->prev) && !((*cutdlst)->next))
	{
		*cutdlst = (t_dlist *)0;
		return (clst);
	}
	if ((*cutdlst)->prev)
		(*cutdlst)->prev->next = (*cutdlst)->next;
	else
		(*cutdlst) = (*cutdlst)->next;
	if ((*cutdlst)->next)
		(*cutdlst)->next->prev = (*cutdlst)->prev;
	return (clst);
}

static void			x_cache_push_init(t_dlist *row, int	steps[4])
{
	int		i[2];
	char	*row_str;

	i[0] = -1;
	i[1] = 0;
	row_str = row->content;
	while (++(i[0]))
	{
		while (row_str[i[1]] == '.')
			(i[1])++;
		steps[i[0]] = (i[1])++;
	}
}

/*
** Функция удаляет все разногласия для конкретного ряда во всех нижестоящих матрицах.
** При конфликте в начале матрицы ее начало должно переноситься.
** Если одна из следующих матриц теряет все строки, то ее указатель приравнивается к 0.
*/
static void			x_cache_push(t_dlist **matrix, t_dlist *row, t_dlist *cache)
{
	int			step[4];
	t_dlist		*cut_row;
	t_dlist		*cutted;
	char		*str;

	x_cache_push_init(row, step);
	matrix++;
	while ((*matrix)->content)
	{
		cut_row = (*matrix);
		while (cut_row && (str = cut_row->content))
		{
			cutted = cut_row;
			cut_row = cut_row->next;
			if (str[step[0]] != '.' || str[step[1]] != '.' \
			|| str[step[2]] != '.' || str[step[3]] != '.')
			{
				cutted = spec_dlst_cut(&cutted);
			}
		}
		matrix++;
	}
}

static char			*x_do_it(t_dlist **matrix, t_dlist *row, char *result)
{
	t_dlist		*cache; // кеш представляет из себя двусвязанный список. в начале стоит

	if (!(*matrix))
		return (0);
	if (!((*matrix)->content))
		return (result); // сюда заходит на последней матрице, в нашем массиве последняя матрица "не имеет контента"
	while (row)
	{
		x_cache_push(matrix, row, cache);
		if (!(x_do_it((matrix + 1), *(matrix + 1), result)))
		{
			x_cache_pull(matrix, cache);
			row = row->next;
		}
		else
		{
			return (result); // ЕЩЕ ОДИН ПОЛОЖИТЕЛЬНЫЙ ИСХОД.
		}
	}
	return (0);
}

/*
** Иницилизация решения алгоритмом Х
*/
static char			*x_init(unsigned short *ttrs, int square)
{
	t_dlist		**matrix;
	char		*result;

	matrix = (t_dlist **)matrix_init(ttrs, square);
	result = (char *)malloc(square * square);
	ft_memset(result, '.', square * square);
	return (x_do_it(matrix, *matrix, result));
}

/*
** Запуск Алгоритма Х для квадрата определнной длины.
*/
static void			solver(unsigned short *ttrs)
{
	const int	size = ttrs_size(ttrs);
	int			square;

	square = sqrt_ceil(size * 4);
	while (!x_init(ttrs, square))
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
