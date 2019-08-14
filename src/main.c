/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:44:43 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/14 15:09:54 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		main(int ac, char **av)
{
	int		n;
	t_node	*stock;
	char	*str;

	if (ac != 2)
	{
		ft_printf("not correct input");
		return (0);
	}
	n = 0;
	stock = 0;
	str	= av[1];
	///parse();
	return (0);
}
