/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:02 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/11 20:53:38 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*a;

	a = (char*)s;
	i = 0;
	if (c == 256)
		return ("");
	while (a[i])
	{
		if (a[i] == (char)c)
			return (&a[i]);
		i++;
	}
	if (c == 0)
		return (&a[i]);
	return (0);
}
