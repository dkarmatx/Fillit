/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris-map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 04:59:17 by hgranule          #+#    #+#             */
/*   Updated: 2019/04/29 10:08:39 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraminos.h"

void	draw_tmap(char mp[MS][MS + 1], unsigned short tetr, \
int crd[2], char c)
{
	int		i;

	i = 4;
	while (--i >= 0)
	{
		if (tetr & 8)
			mp[crd[1] + i][crd[0]] = c;
		if (tetr & 4)
			mp[crd[1] + i][crd[0] + 1] = c;
		if (tetr & 2)
			mp[crd[1] + i][crd[0] + 2] = c;
		if (tetr & 1)
			mp[crd[1] + i][crd[0] + 3] = c;
		tetr >>= 4;
	}
}

int		try_pos(char mp[MS][MS + 1], unsigned short tetr, int crd[2])
{
	int		i;

	i = 4;
	while (--i >= 0)
	{
		if (tetr & 8)
			if (mp[crd[1] + i][crd[0]] != '.')
				return (0);
		if (tetr & 4)
			if (mp[crd[1] + i][crd[0] + 1] != '.')
				return (0);
		if (tetr & 2)
			if (mp[crd[1] + i][crd[0] + 2] != '.')
				return (0);
		if (tetr & 1)
			if (mp[crd[1] + i][crd[0] + 3] != '.')
				return (0);
		tetr >>= 4;
	}
	return (1);
}
