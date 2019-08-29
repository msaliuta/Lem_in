/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:08:53 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/29 17:09:51 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_nbr(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!(ft_isdigit(line[i])) && line[i] != '-' && line[i] != ' ')
			terminate("Coords are not valid");
	if (ft_atol(line) > 2147483647)
		terminate("Coords are not valid");
	return (1);
}

t_room	*new_room(char *line)
{
	t_room		*tmp;
	const int	n = ft_strchr(line, ' ') - line;

	if (!(tmp = ft_memalloc(sizeof(t_room))))
		terminate("No memory");
	tmp->name = ft_memalloc(sizeof(char) * (n + 1));
	ft_memcpy(tmp->name, line, n);
	line = ft_strchr(line, ' ') + 1;
	check_nbr(line) ? tmp->x = ft_atoi(line) : 0;
	line = ft_strchr(line, ' ') + 1;
	tmp->y = ft_atoi(line);
	tmp->lvl = -1;
	tmp->links = new_array(4);
	return (tmp);
}
