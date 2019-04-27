/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetromino-parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:42:25 by hgranule          #+#    #+#             */
/*   Updated: 2019/04/27 17:22:17 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" //ДЛЯ ДЕБАГИНГА
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
		return (0);
	if (a[4] != '\n' || a[9] != '\n' || a[14] != '\n' || a[19] != '\n')
		return (0);
	if ((count = tetromino_encode(a, &tetr)) < 1 || count > 4)
		return (0);
	tetromino_padding(&tetr);
	tetromino_masks(&tetr);
	return (tetr);
}

static int				test_tetro_valid(void)
{
	char *ih = 
	"....\n"
	"....\n"
	"####\n"
	"....\n";

	char *iv =
	"..#.\n"
	"..#.\n"
	"..#.\n"
	"..#.\n";

	char *l1 =
	"....\n"
	"..#.\n"
	"..#.\n"
	"..##\n";

	char *l2 =
	"....\n"
	"###.\n"
	"#...\n"
	"....\n";

	char *l3 =
	"##..\n"
	"#...\n"
	"#...\n"
	"....\n";

	char *l4 =
	"....\n"
	"....\n"
	"...#\n"
	".###\n";

	char *j1 =
	"..#.\n"
	"..#.\n"
	".##.\n"
	"....\n";

	char *j2 =
	"....\n"
	"#...\n"
	"###.\n"
	"....\n";

	char *j3 =
	"..##\n"
	"..#.\n"
	"..#.\n"
	"....\n";

	char *j4 =
	"....\n"
	"....\n"
	"###.\n"
	"..#.\n";

	char *t1 =
	"....\n"
	"###.\n"
	".#..\n"
	"....\n";

	char *t2 =
	"....\n"
	"...#\n"
	"..##\n"
	"...#\n";

	char *t3 =
	"..#.\n"
	".###\n"
	"....\n"
	"....\n";

	char *t4 =
	"....\n"
	".#..\n"
	".##.\n"
	".#..\n";

	char *zh =
	"....\n"
	".##.\n"
	"..##\n"
	"....\n";

	char *zv =
	"....\n"
	"...#\n"
	"..##\n"
	"..#.\n";

	char *sh =
	"....\n"
	"....\n"
	".##.\n"
	"##..\n";

	char *sv =
	"....\n"
	"#...\n"
	"##..\n"
	".#..\n";

	char *o1 =
	"....\n"
	"....\n"
	"##..\n"
	"##..\n";

	char *e1 =
	"....\n"
	"....\n"
	"#a..\n"
	"##..\n";

	char *e2 =
	"....\n"
	"..#.\n"
	"##..\n"
	"##..\n";

	char *e3 =
	"...#\n"
	"..#.\n"
	".#..\n"
	"#...\n";

	char *e4 =
	"....\n"
	"....\n"
	".\n"
	"...\n";

	char *e5 =
	"\n"
	"\n"
	"\n"
	"\n";

	char *e6 =
	"....\n"
	".#...\n"
	"##..\n"
	"#...\n";

	char *e7 = (void *)0;

	unsigned short tih = tetromino_parser(ih);
	unsigned short tiv = tetromino_parser(iv);

	unsigned short tl1 = tetromino_parser(l1);
	unsigned short tl2 = tetromino_parser(l2);
	unsigned short tl3 = tetromino_parser(l3);
	unsigned short tl4 = tetromino_parser(l4);

	unsigned short tj1 = tetromino_parser(j1);
	unsigned short tj2 = tetromino_parser(j2);
	unsigned short tj3 = tetromino_parser(j3);
	unsigned short tj4 = tetromino_parser(j4);

	unsigned short tt1 = tetromino_parser(t1);
	unsigned short tt2 = tetromino_parser(t2);
	unsigned short tt3 = tetromino_parser(t3);
	unsigned short tt4 = tetromino_parser(t4);

	unsigned short tzh = tetromino_parser(zh);
	unsigned short tzv = tetromino_parser(zv);

	unsigned short tsh = tetromino_parser(sh);
	unsigned short tsv = tetromino_parser(sv);

	unsigned short to1 = tetromino_parser(o1);

	unsigned short te1 = tetromino_parser(e1);
	unsigned short te2 = tetromino_parser(e2);
	unsigned short te3 = tetromino_parser(e3);
	unsigned short te4 = tetromino_parser(e4);
	unsigned short te5 = tetromino_parser(e5);
	unsigned short te6 = tetromino_parser(e6);
	unsigned short te7 = tetromino_parser(e7);

	if (tih == TETR_I_H)
		ft_putendl("tih");
	if (tiv == TETR_I_V)
		ft_putendl("tiv");

	if (tl1 == TETR_L_1)
		ft_putendl("tl1");
	if (tl2 == TETR_L_2)
		ft_putendl("tl2");
	if (tl3 == TETR_L_3)
		ft_putendl("tl3");
	if (tl4 == TETR_L_4)
		ft_putendl("tl4");

	if (tj1 == TETR_J_1)
		ft_putendl("tj1");
	if (tj2 == TETR_J_2)
		ft_putendl("tj2");
	if (tj3 == TETR_J_3)
		ft_putendl("tj3");
	if (tj4 == TETR_J_4)
		ft_putendl("tj4");

	if (tt1 == TETR_T_1)
		ft_putendl("tt1");
	if (tt2 == TETR_T_2)
		ft_putendl("tt2");
	if (tt3 == TETR_T_3)
		ft_putendl("tt3");
	if (tt4 == TETR_T_4)
		ft_putendl("tt4");

	if (tsh == TETR_S_H)
		ft_putendl("tsh");
	if (tsv == TETR_S_V)
		ft_putendl("tsv");

	if (tzh == TETR_Z_H)
		ft_putendl("tzh");
	if (tzv == TETR_Z_V)
		ft_putendl("tzv");

	if (to1 == TETR_O_1)
		ft_putendl("to1");

	return (0);
}