/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:27 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/06 14:54:49 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *s)
{
	long	n;
	int		np;

	np = 1;
	n = 0;
	while (*s == '\t' || *s == ' ' || *s == '\n' ||
			*s == '\r' || *s == '\v' || *s == '\f')
		++s;
	*s == '-' ? np = -1 : 0;
	*s == '-' || *s == '+' ? ++s : 0;
	while ((*s >= '0') && (*s <= '9'))
	{
		n *= 10;
		n += *s - 48;
		++s;
	}
	return ((int)n * np);
}
