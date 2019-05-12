/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:27:59 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/13 02:43:38 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraminos.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

t_dlist				**g_matrix_watch;

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
		{
			ft_strdel(&str);
			return (0);
		}
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

static void			x_finish_him(char *res, char *row)
{
	while (*row)
	{
		if (*row != '.')
			*res = *row;
		res++;
		row++;
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
	t_dlist		*cb;
	t_dlist		*c;

	while (*cache)
	{
		cur_cached = (t_dlist *)(*cache)->content;
		ft_dlstinsert(cur_cached, cur_cached->prev, cur_cached->next);
		c = *cache;
		(*cache) = (*cache)->next;
		free(c);
	}
	while (*cache_b)
	{
		matrix++;
		(*matrix) = (*cache_b)->content;
		c = *cache_b;
		(*cache_b) = (*cache_b)->next;
		free(c);
	}
}

/*
** Функция удаляет все разногласия для конкретного ряда во всех нижестоящих матрицах.
** При конфликте в начале матрицы ее начало должно переноситься.
** Если одна из следующих матриц теряет все строки, то ее указатель приравнивается к 0.
*/
static char		x_cache_push(t_dlist **matrix, t_dlist *row, t_dlist **cache)
{
	int			step[4];
	t_dlist		*cutted;
	char		*str;

	x_cache_push_init(row, step);
	while ((row = *(++matrix)) && (*(matrix))->content)
	{
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
		if (*matrix == 0)
			return (0);
	}
	if (row == 0)
		return (0);
	return (1);
}

static char			x_cache_b_push(t_dlist **matrix, t_dlist **cache_b)
{
	while (!(*(++matrix)) || (*(matrix))->content)
	{
		if (*cache_b)
			ft_dlstunshift(cache_b, ft_dlstnew(0, 0));
		else
			*cache_b = ft_dlstnew(0, 0);
		(*cache_b)->content = (*matrix);
		(*cache_b)->size = (sizeof(t_dlist *));
	}
	if (*matrix == 0)
		return (0);
	return (1);
}

static char			*x_do_it(t_dlist **matrix, t_dlist *row, char *result)
{
	t_dlist		*cache; // кеш представляет из себя двусвязанный список. в начале стоит
	t_dlist		*cache_b; // кеш начальных элементов.
	char		cs[2];

	cache = 0;
	cache_b = 0;
	if (!(*matrix))
		return (0);
	if (!((*matrix)->content))
		return (result); // сюда заходит на последней матрице, в нашем массиве последняя матрица "не имеет контента"
	while (row)
	{
		cs[0] = x_cache_b_push(matrix, &cache_b);
		cs[1] = x_cache_push(matrix, row, &cache);
		if (!cs[0] || !cs[1] || !(x_do_it((matrix + 1), *(matrix + 1), result)))
		{
			x_cache_pull(matrix, &cache, &cache_b);
			row = row->next;
		}
		else
		{
			x_finish_him(result, row->content);
			x_cache_pull(matrix, &cache, &cache_b);
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
	t_dlist		**rm;
	char		*result;
	char		*b;

	matrix = (t_dlist **)matrix_init(ttrs, square);
	result = (char *)malloc(square * square);
	ft_memset(result, '.', square * square);
	g_matrix_watch = matrix;
	b = x_do_it(matrix, *matrix, result);
	rm = matrix;
	while (((*rm)->content))
	{
		if (*rm != 0)
			ft_dlstdel(rm, (size_t)-1);
		rm++;
	}
	if (*rm != 0)
		ft_dlstdel(rm, (size_t)-1);
	free(matrix);
	if (!b)
		ft_strdel(&result);
	return (result);
}

/*
** Запуск Алгоритма Х для квадрата определнной длины.
*/
static void			solver(unsigned short *ttrs)
{
	const int	size = ttrs_size(ttrs);
	int			square;
	int			row;
	char		*result;

	square = sqrt_ceil(size * 4);
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
