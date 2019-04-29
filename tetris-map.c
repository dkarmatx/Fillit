/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris-map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 04:59:17 by hgranule          #+#    #+#             */
/*   Updated: 2019/04/29 07:23:09 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraminos.h"

void	draw_tmap(char mp[MS][MS + 1], unsigned short tetr, \
int crd[2], char c)
{
	int				i;

	i = 4;
	while (--i >= 0)
	{
		if (tetr & 8)
			mp[crd[1] + i][crd[0] + 0] = c;
		if (tetr & 4)
			mp[crd[1] + i][crd[0] + 1] = c;
		if (tetr & 2)
			mp[crd[1] + i][crd[0] + 2] = c;
		if (tetr & 1)
			mp[crd[1] + i][crd[0] + 3] = c;
		tetr >>= 4;
	}
}