/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 18:36:06 by msaliuta          #+#    #+#             */
/*   Updated: 2018/11/04 16:13:47 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	len_1;
	size_t	len_2;
	size_t	len_max;
	int		r;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	if (len_1 > len_2)
		len_max = len_1;
	else
		len_max = len_2;
	r = ft_memcmp(s1, s2, len_max);
	return (r);
}
