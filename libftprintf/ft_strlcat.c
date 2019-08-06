/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 18:57:46 by msaliuta          #+#    #+#             */
/*   Updated: 2018/11/04 14:25:33 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char	*i;
	char	*j;
	size_t	k;
	size_t	dln;

	i = (char*)dest;
	j = (char*)src;
	k = size;
	while ((k-- != 0) && *i != '\0')
		i++;
	dln = i - dest;
	k = size - dln;
	if (k == 0)
		return (dln + ft_strlen(j));
	while (*j != '\0')
	{
		if (k != 1)
		{
			*i++ = *j;
			k--;
		}
		j++;
	}
	*i = '\0';
	return (dln + (j - src));
}
