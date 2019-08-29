/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 16:47:08 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/29 19:20:01 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	parse_l(t_room **rooms, t_struct *lemin, t_input *input)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(0, &line) > 0)
	{
		input->next = save_input(line);
		input = input->next;
		(line[0] == '#' && i != 0) ? terminate("error") : 0;
		if (lemin->ants == 0 && check_ants(line))
			lemin->ants = ft_atoi(line);
		else if (line[0] == '#' && line[1] == '#' && i == 0 && lemin->ants)
		{
			ft_strequ(line, "##start") ? (i = 1) : 0;
			ft_strequ(line, "##end") ? (i = 2) : 0;
		}
		else if (ft_chr_count(line, ' ') == 2 && *line != 'L' && lemin->ants)
			set_room(rooms, lemin, line, i) ? (i = 0) : 0;
		else if (ft_chr_count(line, '-') && line[0] != '#' && i == 0)
			set_link(lemin, *rooms, line) && (lemin->links = 1);
		else if (line[0] == '#')
			continue ;
		else
			terminate("Input invalid");
	}
}

t_input	*save_input(char *line)
{
	t_input	*tmp;

	tmp = (t_input*)malloc(sizeof(t_input));
	tmp->next = NULL;
	tmp->str = line;
	return (tmp);
}

int		check_ants(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!(ft_isdigit(line[i]) && !(i == 0 && line[1] == '-')))
			return (0);
	if (ft_atol(line) > 2147483647 || ft_atol(line) < 1 || ft_strlen(line) > 11)
		return (0);
	return (1);
}

bool	set_room(t_room **rooms, t_struct *lemin, char *line, int n)
{
	t_room	*tmp;

	lemin->links ? terminate("Room after links") : 0;
	lemin->count_of_rooms++;
	tmp = *rooms;
	if (tmp->name == NULL)
	{
		free(*rooms);
		*rooms = new_room(line);
		tmp = *rooms;
	}
	else
	{
		tmp = *rooms;
		while (tmp->next)
			check_roomd(line, tmp) ? tmp = tmp->next : 0;
		check_roomd(line, tmp);
		tmp->next = new_room(line);
		tmp = tmp->next;
	}
	if ((n == 1 && lemin->start) || (n == 2 && lemin->end))
		terminate("Duplicate command");
	n == 1 ? lemin->start = tmp : 0;
	n == 2 ? lemin->end = tmp : 0;
	return (true);
}

int		set_link(t_struct *lemin, t_room *lst, char *line)
{
	int		i;
	t_room	*room_a;
	t_room	*room_b;
	char	*name_from;
	char	*name_to;

	(!(lemin->start) || !(lemin->end)) ? terminate("No start or end room") : 0;
	i = 0;
	room_a = lst;
	room_b = lst;
	name_from = ft_memalloc(sizeof(char) * (ft_strchr(line, '-') - line + 1));
	name_to = ft_strdup(ft_strchr(line, '-') + 1);
	ft_memcpy(name_from, line, ft_strchr(line, '-') - line);
	is_room_exist(&room_a, &room_b, &name_from, &name_to);
	while (room_a->links->links[i])
		++i == room_a->links->limit ? expandable_arr(&room_a->links) : 0;
	(room_a->links->links[i] = room_b) && (room_a->links->size++);
	!(room_a->links->links[++i] = NULL) ? ft_bzero(&i, sizeof(int)) : 0;
	while (room_b->links->links[i])
		++i == room_b->links->limit ? expandable_arr(&room_b->links) : 0;
	(room_b->links->links[i] = room_a) && (room_b->links->size++);
	room_b->links->links[++i] = NULL;
	free(name_to);
	free(name_from);
	return (1);
}
