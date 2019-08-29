/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:20:17 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/29 15:24:22 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	bfs_run(t_room *rooms, t_array *paths, t_struct *lemin)
{
	while (path_find(lemin))
	{
		path_create(lemin, &paths);
		if (paths[0].size == 1)
			break ;
		zero(rooms);
		block(lemin->n_path, paths);
	}
}

bool	path_find(t_struct *lemin)
{
	t_room	**queue;
	int		start;
	int		end;

	queue = ft_memalloc(sizeof(t_room*) * lemin->count_of_rooms + 1);
	start = 0;
	end = 1;
	lemin->start->lvl = 0;
	queue[start] = lemin->start;
	while (start != end)
	{
		if (queue[start] == lemin->end)
			break ;
		bfs(queue, queue[start], &end);
		start++;
	}
	free(queue);
	return (!(lemin->end->parent == NULL));
}


void	path_create(t_struct *lemin, t_array **paths)
{
	t_room	*tmp;

	(*paths)[lemin->n_path].size = lemin->end->lvl;
	(*paths)[lemin->n_path].links = malloc(sizeof(t_room*) * lemin->end->lvl);
	tmp = lemin->end;
	while (tmp != lemin->start)
	{
		(*paths)[lemin->n_path].links[tmp->lvl - 1] = tmp;
		tmp = tmp->parent;
	}
	lemin->n_path += 1;
}

void	zero(t_room *rooms)
{
	t_room	*tmp;

	tmp = rooms;
	while (tmp)
	{
		tmp->lvl = -1;
		tmp->parent = NULL;
		tmp = tmp->next;
	}
}

void	block(int n_path, t_array *paths)
{
	int	path;
	int	room;

	path = -1;
	while (++path < n_path && (room = -1))
		while (++room < paths[path].size - 1)
			paths[path].links[room]->lvl = -2;
}
