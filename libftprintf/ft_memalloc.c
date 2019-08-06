/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 18:32:38 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/11 20:47:41 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	size_t	i;
	char	*ptr;

	i = -1;
	ptr = (char*)malloc(size);
	if (ptr)
		while (++i < size)
			ptr[i] = 0;
	else
		return (NULL);
	ft_bzero(ptr, size);
	return (ptr);
}
