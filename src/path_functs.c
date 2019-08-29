/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:57:11 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/29 17:01:37 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	display_paths(char *start, int n_path, t_array *paths)
{
	int	path;
	int	room;

	path = -1;
	while (++path < n_path && (room = -1))
	{
		ft_printf("%s-->", start);
		while (++room < paths[path].size)
			ft_printf("%s%s", paths[path].links[room]->name,
			room == paths[path].size - 1 ? "\n" : "-->");
	}
}

int		find_free_path(int n_path, t_array *paths)
{
	int	i;

	i = -1;
	while (++i < n_path)
		if (paths[i].size == 1 || paths[i].links[0]->ants == 0)
			return (i);
	return (-1);
}

int		count_sum_of_paths(t_array *paths, int n)
{
	int	i;
	int	sum;

	if (n == 0)
		return (0);
	i = -1;
	sum = 0;
	while (++i < n)
		sum += (paths[n].size - paths[i].size);
	return (sum);
}

bool	expandable_arr(t_array **old)
{
	int		i;
	t_room	**tmp_links;

	i = -1;
	tmp_links = (*old)->links;
	if ((*old)->limit < 100)
		(*old)->limit = (*old)->limit * 3;
	else
		(*old)->limit = (*old)->limit * 2;
	if (!((*old)->links = ft_memalloc(sizeof(t_room *) * (*old)->limit)))
		terminate("No memory");
	while (++i < (*old)->size && tmp_links)
		(*old)->links[i] = tmp_links[i];
	(*old)->links[++i] = NULL;
	free(tmp_links);
	return (true);
}

void	go_ants(t_struct *lemin, t_array *paths)
{
	int		**ants;
	int		i;

	ants = malloc(sizeof(int*) * lemin->ants);
	i = -1;
	while (++i < lemin->ants)
		(ants[i] = (int*)ft_memalloc(sizeof(int) * 2))
		&& (ants[i][0] = -1);
	lemin->ants_left = lemin->ants;
	while (lemin->end->ants != lemin->ants)
	{
		step(ants, paths, lemin);
		ft_printf("\n");
	}
	i = -1;
	while (++i < lemin->ants)
		free(ants[i]);
	free(ants);
}
