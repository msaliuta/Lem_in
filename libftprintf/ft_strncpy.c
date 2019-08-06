/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 20:02:19 by msaliuta          #+#    #+#             */
/*   Updated: 2018/11/01 17:05:56 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	n;

	n = ft_strlen(src);
	i = -1;
	while (++i < len)
		if (i < n)
			dst[i] = src[i];
		else if (i >= n)
			dst[i] = '\0';
	return (dst);
}
