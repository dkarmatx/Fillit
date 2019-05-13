/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 23:47:36 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/13 04:36:18 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "tetraminos.h"

void		invalid_tetr_handler(void)
{
	ft_putendl("error");
	exit(1);
}

void		x_finish_him(char *res, char *row)
{
	while (*row)
	{
		if (*row != '.')
			*res = *row;
		res++;
		row++;
	}
}
