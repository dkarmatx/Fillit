/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:21:31 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/13 05:44:49 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tetraminos.h"
#include <unistd.h>
#include <stdlib.h>

size_t		ttrs_size(unsigned short *ttrs)
{
	size_t		len;

	len = 0;
	while (*(ttrs++) != 0)
		len++;
	return (len);
}

void		ttrs_input(int fd, unsigned short ttrs[MT + 1])
{
	unsigned short	temp_ttr;
	size_t			len;
	ssize_t			rmem;
	char			buff[VALID_TTR_SYM_COUNT + 2];

	ft_bzero(ttrs, MT + 1);
	rmem = 0;
	while (rmem != 20 && (rmem = read(fd, buff, VALID_TTR_SYM_COUNT + 1)) > 0)
	{
		buff[VALID_TTR_SYM_COUNT + 1] = 0;
		if (rmem < 20 || !(temp_ttr = tetromino_parser(buff)))
			invalid_tetr_handler();
		len = ttrs_size(ttrs);
		ttrs[len] = temp_ttr;
	}
	if (rmem != 20)
		invalid_tetr_handler();
	ttrs[MT] = 0;
}
