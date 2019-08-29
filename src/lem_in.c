/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:27:19 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/29 17:09:38 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	terminate(char *message)
{
	ft_printf("ERROR: %s\n", message);
	exit(1);
}

int		main(int ac, char **av)
{
	t_room		*rooms;
	t_struct	*lemin;
	t_input		*input;
	t_array		*paths;

	input = ft_memalloc(sizeof(t_input));
	lemin = ft_memalloc(sizeof(t_struct));
	rooms = ft_memalloc(sizeof(t_room));
	(ac > 2 || !av) ? terminate("not valid ac number") : 0;
	if (ac == 2 && (ft_strequ(av[1], "-h") || (av[1][1] != 'p' &&
	av[1][1] != 'o' && av[1][1] != 'l') || av[1][0] != '-' || !av[1][1]))
		return (display_man());
	parse_l(&rooms, lemin, input);
	(!lemin->links) ? terminate("No links") : 0;
	paths = ft_memalloc(sizeof(t_array) *
				ft_min(lemin->start->links->size, lemin->end->links->size));
	bfs_run(rooms, paths, lemin);
	(!lemin->n_path) ? terminate("No paths") : 0;
	ft_strequ(av[1], "-o") ? 0 : print_input(input);
	go_ants(lemin, paths);
	ft_strequ(av[1], "-p") ? display_paths(lemin->start->name,
	lemin->n_path, paths) : 0;
	ft_strequ(av[1], "-l") ? system("leaks -q lem-in") : 0;
	return (0);
}
