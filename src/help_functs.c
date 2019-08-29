/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_functs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:26:54 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/29 15:32:40 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		display_man(void)
{
	ft_printf("To use it: ./lem-in < map\n");
	ft_printf("And you can use flag: ./lem-in [-flag] < map\n");
	ft_printf("To look at foud ways use flag: [-p]\n");
	ft_printf("To look at my lem-in help use flag: [-h]\n");
	ft_printf("To check leaks use flag: [-l]\n");
	ft_printf("To hide input use flag: [-o]\n");
	return (0);
}

void	free_paths(int n_path, t_array *paths)
{
	int	path;

	path = -1;
	while (++path < n_path)
		free(paths[path].links);
}

int		ft_min(int a, int b)
{
	return (a < b ? a : b);
}

void	bfs(t_room **queue, t_room *curr, int *end)
{
	int	i;

	i = -1;
	while (++i < curr->links->size)
	{
		if (curr->links->links[i]->lvl == -1)
		{
			curr->links->links[i]->lvl = curr->lvl + 1;
			curr->links->links[i]->parent = curr;
			queue[(*end)++] = curr->links->links[i];
		}
	}
}

void	print_input(t_input *input)
{
	while ((input = input->next))
		ft_printf("%s\n", input->str);
	ft_printf("\n");
}
