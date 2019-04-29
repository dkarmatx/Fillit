/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetromino-parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:42:25 by hgranule          #+#    #+#             */
/*   Updated: 2019/04/29 07:41:19 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraminos.h"

static unsigned short	tetromino_masks(unsigned short *t)
{
	if (TETR_I_H == *t || TETR_I_V == *t)
		return (*t);
	if (TETR_J_1 == *t || TETR_J_2 == *t || TETR_J_3 == *t || TETR_J_4 == *t)
		return (*t);
	if (TETR_L_1 == *t || TETR_L_2 == *t || TETR_L_3 == *t || TETR_L_4 == *t)
		return (*t);
	if (TETR_T_1 == *t || TETR_T_2 == *t || TETR_T_3 == *t || TETR_T_4 == *t)
		return (*t);
	if (TETR_S_H == *t || TETR_S_V == *t)
		return (*t);
	if (TETR_Z_H == *t || TETR_Z_V == *t)
		return (*t);
	if (TETR_O_1 == *t)
		return (*t);
	*t = 0;
	return (*t);
}

static int				tetromino_encode(char *a, unsigned short *tetr)
{
	unsigned int		*row;
	unsigned short		i;
	int					count;

	i = 0;
	count = 1;
	row = (unsigned int *)a;
	while (i < 4)
	{
		if (((0x23232323 ^ *row) & (0x2E2E2E2E ^ *row)) != 0)
			return (0);
		if ((*row & 0xFF000000) == 0x23000000 && count++)
			*tetr += 1;
		if ((*row & 0x00FF0000) == 0x00230000 && count++)
			*tetr += 2;
		if ((*row & 0x0000FF00) == 0x00002300 && count++)
			*tetr += 4;
		if ((*row & 0x000000FF) == 0x00000023 && count++)
			*tetr += 8;
		if (i++ < 3)
			*tetr <<= 4;
		row = (unsigned int *)&(a[i * 5]);
	}
	return (count - 1);
}

static int				tetromino_padding(unsigned short *tetr)
{
	while ((0b1000100010001000 & *tetr) == 0)
		*tetr <<= 1;
	while ((0b1111000000000000 & *tetr) == 0)
		*tetr <<= 4;
	return (0);
}

unsigned short			tetromino_parser(char *a)
{
	unsigned short		tetr;
	int					count;

	tetr = 0;
	if (!a || !(*a))
		invalid_tetr_handler();
	if (a[4] != '\n' || a[9] != '\n' || a[14] != '\n' || a[19] != '\n')
		invalid_tetr_handler();
	if ((count = tetromino_encode(a, &tetr)) < 1 || count > 4)
		invalid_tetr_handler();
	tetromino_padding(&tetr);
	tetromino_masks(&tetr);
	return (tetr);
}
