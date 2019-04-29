/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit-input.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 21:33:50 by hgranule          #+#    #+#             */
/*   Updated: 2019/04/29 07:38:11 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_INPUT_H
# define FILLIT_INPUT_H

# include "libft.h"

# define VALID_TTR_SYM_COUNT 20
# define MAX_TETROMINOS 26
# define MAX_SQUARE 16
# define MS MAX_SQUARE
# define MT MAX_TETROMINOS

void			ttrs_input(int fd, unsigned short ttrs[MT + 1]);
size_t			ttrs_size(unsigned short *ttrs);

#endif