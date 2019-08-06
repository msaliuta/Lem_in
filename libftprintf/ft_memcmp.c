/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:47:31 by msaliuta          #+#    #+#             */
/*   Updated: 2018/11/01 17:19:01 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1c;
	unsigned char	*s2c;
	size_t			i;

	s1c = (unsigned char*)s1;
	s2c = (unsigned char*)s2;
	i = -1;
	while (++i < n)
		if (s1c[i] != s2c[i])
			return (s1c[i] - s2c[i]);
	return (0);
}
