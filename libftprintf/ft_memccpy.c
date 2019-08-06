/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:44:45 by msaliuta          #+#    #+#             */
/*   Updated: 2018/11/01 17:33:42 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_c;
	unsigned char	*src_c;
	size_t			i;

	dst_c = (unsigned char*)dst;
	src_c = (unsigned char*)src;
	i = -1;
	while (++i < n)
	{
		dst_c[i] = src_c[i];
		if (src_c[i] == (unsigned char)c)
			return ((void*)(dst_c + 1 + i));
	}
	return (NULL);
}
