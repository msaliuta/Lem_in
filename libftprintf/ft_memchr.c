/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:46:25 by msaliuta          #+#    #+#             */
/*   Updated: 2018/11/04 12:55:17 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*pr;
	size_t			i;

	pr = (unsigned char*)s;
	i = -1;
	while (++i < n)
		if (pr[i] == (unsigned char)c)
			return ((void*)(pr + i));
	return (NULL);
}
