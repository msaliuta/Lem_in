/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:48:10 by msaliuta          #+#    #+#             */
/*   Updated: 2018/10/31 14:17:49 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dst_c;
	char	*src_c;
	size_t	i;

	dst_c = (char*)dst;
	src_c = (char*)src;
	i = -1;
	while (++i < n)
		dst_c[i] = src_c[i];
	return (dst);
}
