/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgranule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 18:20:39 by hgranule          #+#    #+#             */
/*   Updated: 2019/05/16 18:35:30 by hgranule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*malloc_safe(size_t n)
{
	const void		*mem = malloc(n);

	if (!mem)
	{
		ft_putendl("malloc returned NULL");
		exit(1);
	}
	return (mem);
}

t_dlist	*dlstnew_safe(void *content, size_t size)
{
	const t_dlist	*list = ft_dlstnew(content, size);

	if (!list)
	{
		ft_putendl("ft_dlstnew returned NULL");
		exit(1);
	}
	return (list);
}
