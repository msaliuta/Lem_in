/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:50:20 by msaliuta          #+#    #+#             */
/*   Updated: 2018/11/04 14:21:11 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*dst_c;
	char	*src_c;
	size_t	i;
	int		int_n;

	i = -1;
	int_n = (int)n;
	dst_c = (char*)dst;
	src_c = (char*)src;
	if (src_c < dst_c)
		while (--int_n >= 0)
			dst_c[int_n] = src_c[int_n];
	else
		while (++i < n)
			dst_c[i] = src_c[i];
	return (dst);
}
