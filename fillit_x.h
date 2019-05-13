/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_x.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 04:38:07 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/13 04:41:50 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_X_H
# define FILLIT_X_H

# include "tetraminos.h"

char		*x_do_it(t_dlist **matrix, t_dlist *row, char *result);
int			sqrt_ceil(int b);
char		*str_gen(unsigned short ttr, char c, int square, int step);
t_dlist		*matrix_gen(unsigned short ttr, char c, int square);
t_dlist		**matrix_init(unsigned short *ttrs, int square);

#endif
