/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetraminos.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 04:58:10 by hgranule          #+#    #+#             */
/*   Updated: 2019/04/27 17:17:50 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRAMINOS_H
# define TETRAMINOS_H

# define TETR_I_H (unsigned short)0b1111000000000000
# define TETR_I_V (unsigned short)0b1000100010001000

# define TETR_L_1 (unsigned short)0b1000100011000000
# define TETR_L_2 (unsigned short)0b1110100000000000
# define TETR_L_3 (unsigned short)0b1100100010000000
# define TETR_L_4 (unsigned short)0b0010111000000000

# define TETR_J_1 (unsigned short)0b0100010011000000
# define TETR_J_2 (unsigned short)0b1000111000000000
# define TETR_J_3 (unsigned short)0b1100100010000000
# define TETR_J_4 (unsigned short)0b1110001000000000

# define TETR_T_1 (unsigned short)0b1110010000000000
# define TETR_T_2 (unsigned short)0b0100110001000000
# define TETR_T_3 (unsigned short)0b0100111000000000
# define TETR_T_4 (unsigned short)0b1000110010000000

# define TETR_Z_H (unsigned short)0b1100011000000000
# define TETR_Z_V (unsigned short)0b0100110010000000

# define TETR_S_H (unsigned short)0b0110110000000000
# define TETR_S_V (unsigned short)0b1000110001000000

# define TETR_O_1 (unsigned short)0b1100110000000000

/*
** Сюда приходит строка типа "....\n....\n....\n....\n"
** Если в строке содержится валидная тетроминка, то
** она возвращается через return ;
*/
unsigned short		tetromino_parser(char *a);

#endif