/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 18:29:41 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/16 18:35:51 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_MALLOC_H
# define SAFE_MALLOC_H

# include "libft.h"

void	*malloc_safe(size_t n);
t_dlist *dlstnew_safe(void *content, size_t size);

#endif
