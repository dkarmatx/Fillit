/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:27:59 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/10 11:36:20 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraminos.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

t_dlist **G_MATRIX_WATCH;
t_dlist *G_CACHE_WATCH;

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

static void			x_cache_push_init(t_dlist *row, int	steps[4])
{
	int		i[2];
	char	*row_str;

	i[0] = -1;
	i[1] = 0;
	row_str = row->content;
	while (++(i[0]) < 4)
	{
		while (row_str[i[1]] == '.')
			(i[1])++;
		steps[i[0]] = (i[1])++;
	}
}

static void			x_cache_pull(t_dlist **matrix, t_dlist **cache, t_dlist **cache_b)
{
	t_dlist		*cur_cached;

	while (*cache)
	{
		cur_cached = (t_dlist *)(*cache)->content;
		ft_dlstinsert(cur_cached, cur_cached->prev, cur_cached->next);
		(*cache) = (*cache)->next;
	}
	while (*cache_b)
	{
		matrix++;
		(*matrix) = (*cache_b)->content;
		(*cache_b) = (*cache_b)->next;
	}
	return ;
}

/*
** Функция удаляет все разногласия для конкретного ряда во всех нижестоящих матрицах.
** При конфликте в начале матрицы ее начало должно переноситься.
** Если одна из следующих матриц теряет все строки, то ее указатель приравнивается к 0.
*/
static void		x_cache_push(t_dlist **matrix, t_dlist *row, t_dlist **cache)
{
	int			step[4];
	t_dlist		*cutted;
	char		*str;

	x_cache_push_init(row, step);
	while ((*(++matrix))->content && (((row = *matrix)) || 1))
		while (row && (str = row->content))
			if (str[step[0]] != '.' || str[step[1]] != '.' || \
			str[step[2]] != '.' || str[step[3]] != '.')
			{
				cutted = ft_dlstcut(&row);
				if (!row || row->prev == 0)
					(*matrix) = row;
				else
					row = row->next;
				ft_dlstunshift(cache, ft_dlstnew(0, 0));
				(*cache)->content = cutted;
				(*cache)->size = sizeof(t_dlist *);
			}
			else
				row = row->next;
}

static void			x_cache_b_push(t_dlist **matrix, t_dlist **cache_b)
{
	while (!(*(++matrix)) || (*(matrix))->content)
	{
		if (*cache_b)
			ft_dlstpush(cache_b, ft_dlstnew(0, 0));
		else
			*cache_b = ft_dlstnew(0, 0);
		(*cache_b)->content = (*matrix);
		(*cache_b)->size = (sizeof(t_dlist *));
	}
}

static char			*x_do_it(t_dlist **matrix, t_dlist *row, char *result)
{
	t_dlist		*cache; // кеш представляет из себя двусвязанный список. в начале стоит
	t_dlist		*cache_b; // кеш начальных элементов.

	cache = 0;
	cache_b = 0;
	if (!(*matrix))
		return (0);
	if (!((*matrix)->content))
		return (result); // сюда заходит на последней матрице, в нашем массиве последняя матрица "не имеет контента"
	while (row)
	{
		ft_putendl(row->content);
		x_cache_b_push(matrix, &cache_b);
		x_cache_push(matrix, row, &cache);
		if (!(x_do_it((matrix + 1), *(matrix + 1), result)))
		{
			x_cache_pull(matrix, &cache, &cache_b);
			row = row->next;
		}
		else
		{
			ft_putendl(row->content);
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

	G_MATRIX_WATCH = matrix;
	
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
