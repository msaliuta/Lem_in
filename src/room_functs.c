/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_functs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:03:54 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/29 17:06:20 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_room_exist(t_room **r_a, t_room **r_b, char **n_a, char **n_b)
{
	while ((*r_a) && !ft_strequ((*r_a)->name, *n_a))
		*r_a = (*r_a)->next;
	while ((*r_b) && !ft_strequ((*r_b)->name, *n_b))
		*r_b = (*r_b)->next;
	if (!(*r_a) || !(*r_b))
		terminate("Room does not exist");
	return (1);
}

t_array	*new_array(int def_size)
{
	int		i;
	t_array	*new_arr;

	i = 0;
	if (!(new_arr = ft_memalloc(sizeof(t_array))))
		terminate("No memory");
	new_arr->size = 0;
	new_arr->limit = def_size - 1;
	if (!(new_arr->links = ft_memalloc(sizeof(t_room *) * def_size)))
		terminate("No memory");
	while (i < def_size)
		new_arr->links[i++] = NULL;
	return (new_arr);
}

bool	check_roomd(char *line, t_room *tmp)
{
	const char	*i = ft_strchr(line, ' ') + 1;
	const char	*j = ft_strchr(i, ' ') + 1;
	char		*name;

	if (tmp->x == atoi(i) && tmp->y == atoi(j))
		terminate("Room with same  coords");
	name = ft_memalloc(sizeof(char) * (i - line));
	ft_strncpy(name, line, i - line - 1);
	if (ft_strequ(name, tmp->name))
		terminate("Room with same name");
	free(name);
	return (true);
}

void	step(int **ants, t_array *paths, t_struct *lemin)
{
	int		i;
	int		r;

	i = -1;
	while (++i < lemin->ants)
		if (ants[i][0] == -1
			&& ((r = find_free_path(lemin->n_path, paths)) != -1)
			&& ((lemin->ants_left) > count_sum_of_paths(paths, r)))
		{
			--(lemin->ants_left);
			ants[i][0] = r;
			ft_printf("L%d-%s ", i + 1, paths[r].links[ants[i][1]]->name);
			++(paths[r].links[ants[i][1]]->ants);
		}
		else if (ants[i][0] != -1 && paths[ants[i][0]].size - 1 != ants[i][1])
		{
			--(paths[ants[i][0]].links[ants[i][1]]->ants);
			ft_printf("L%d-%s ", i + 1,
			paths[ants[i][0]].links[++ants[i][1]]->name);
			++(paths[ants[i][0]].links[ants[i][1]]->ants);
		}
}
