/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_algorithm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 04:27:42 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/13 04:42:17 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraminos.h"
#include <stdlib.h>

static void		x_cache_push_init(t_dlist *row, int steps[4])
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

static void		x_cache_pull(t_dlist **matrix, t_dlist **cache, \
t_dlist **cache_b)
{
	t_dlist	*cur_cached;
	t_dlist	*cb;
	t_dlist	*c;

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

static char		x_cache_push(t_dlist **matrix, t_dlist *row, t_dlist **cache)
{
	int			step[4];
	char		*str;

	x_cache_push_init(row, step);
	while ((row = *(++matrix)) && (*(matrix))->content)
	{
		while (row && (str = row->content))
			if (str[step[0]] != '.' || str[step[1]] != '.' || \
			str[step[2]] != '.' || str[step[3]] != '.')
			{
				ft_dlstunshift(cache, ft_dlstnew(0, 0));
				(*cache)->content = ft_dlstcut(&row);
				(*cache)->size = sizeof(t_dlist *);
				if (!row || row->prev == 0)
					(*matrix) = row;
				else
					row = row->next;
			}
			else
				row = row->next;
		if (*matrix == 0)
			return (0);
	}
	return (1);
}

static char		x_cache_b_push(t_dlist **matrix, t_dlist **cache_b)
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

char			*x_do_it(t_dlist **matrix, t_dlist *row, char *result)
{
	t_dlist		*cache;
	t_dlist		*cache_b;
	char		cs[2];

	cache = 0;
	cache_b = 0;
	if (!(*matrix))
		return (0);
	if (!((*matrix)->content))
		return (result);
	while (row)
	{
		cs[0] = x_cache_b_push(matrix, &cache_b);
		cs[1] = x_cache_push(matrix, row, &cache);
		if (!cs[0] || !cs[1] || !(x_do_it((matrix + 1), *(matrix + 1), result)))
			x_cache_pull(matrix, &cache, &cache_b);
		else
		{
			x_finish_him(result, row->content);
			x_cache_pull(matrix, &cache, &cache_b);
			return (result);
		}
		row = row->next;
	}
	return (0);
}
