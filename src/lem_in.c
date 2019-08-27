/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:27:19 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/28 00:09:25 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	terminate(char *message)
{
	ft_printf("ERROR: %s\n", message);
	exit(1);
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

int		is_room_exist(t_room **tmp, char *name_from)
{
	while ((*tmp) && !ft_strequ((*tmp)->name, name_from))
		if ((*tmp)->next)
			*tmp = (*tmp)->next;
		else
			terminate("Room does not exist");
	// if (!(*tmp)->links)
	// {
	// 	ft_printf("error: room exist");
	// 	exit(EXIT_FAILURE);
	// }
	return (1);
}

int		set_link(t_room *lst, char *line)
{
	int		i;
	t_room	*room_a;
	t_room	*room_b;
	char	*name_from;
	char	*name_to;

	i = 0;
	room_a = lst;
	room_b = lst;
	name_from = ft_memalloc(sizeof(char) * (ft_strchr(line, '-') - line + 1));
	name_to = ft_strdup(ft_strchr(line, '-') + 1);
	ft_memcpy(name_from, line, ft_strchr(line, '-') - line);
	is_room_exist(&room_a, name_from) && is_room_exist(&room_b, name_to);
	while (room_a->links->links[i])
		++i == room_a->links->limit ? expandable_arr(&room_a->links) : 0;
	(room_a->links->links[i] = room_b) && (room_a->links->size++);
	room_a->links->links[++i] = NULL;
	i = 0;
	while (room_b->links->links[i])
		++i == room_b->links->limit ? expandable_arr(&room_b->links) : 0;
	(room_b->links->links[i] = room_a) && (room_b->links->size++);
	room_b->links->links[++i] = NULL;
	free(name_to);
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
	tmp->dst_from_end = -1;
	tmp->links = new_array(4);
	tmp->full_of_ants = 0;
	tmp->visited = false;
	tmp->parent = NULL;
	tmp->next = NULL;
	return (tmp);
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
	return (true);
}

bool	set_room(t_room **rooms, t_struct *lemin, char *line, int n)
{
	t_room	*tmp;

	if (lemin->links)
		terminate("Room after links");
	lemin->count_of_rooms++;
	tmp = *rooms;
	if (tmp->name == NULL)
	{
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

t_input	*save_input(char *line)
{
	t_input	*tmp;

	tmp = (t_input*)malloc(sizeof(t_input));
	tmp->next = NULL;
	tmp->str = line;
	return (tmp);
}

void	parse_l(t_room *rooms, t_struct *lemin, t_input *input)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (lemin->ants == 0 && check_ants(line))
			lemin->ants = ft_atoi(line);
		else if (line[0] == '#' && line[1] == '#' && i == 0 && lemin->ants > 0)
		{
			ft_strequ(line, "##start") ? (i = 1) : 0;
			ft_strequ(line, "##end") ? (i = 2) : 0;
		}
		else if (line[0] == '#')
			continue ;
		else if (ft_chr_count(line, ' ') == 2 && *line != 'L' && lemin->ants)
			set_room(&rooms, lemin, line, i) ? (i = 0) : 0;
		else if (ft_chr_count(line, '-') && line[0] != '#')
			set_link(rooms, line) && (lemin->links = 1);
		else
			terminate("Input invalid");
		input->next = save_input(line);
		input = input->next;
		// tmp = tmp->next;
		// ft_printf("%s\n", tmp->str);
		//ft_strdel(&line);
	}
}

int	main(int ac, char **av)
{
	//t_array		*ways;
	t_room		*rooms;
	t_struct	*lemin;
	t_input		*input;

	input = ft_memalloc(sizeof(t_input));
	lemin = ft_memalloc(sizeof(t_struct));
	rooms = ft_memalloc(sizeof(t_room));
	if (ac > 2 || !av)
	{
		ft_printf("%s\n", "error: not valid ac number");
		exit(EXIT_FAILURE);
	}
	parse_l(rooms, lemin, input);
	(!lemin->start || !lemin->end) ? terminate("No start or end room") : 0;
	(!lemin->links) ? terminate("No links") : 0;
	while ((input = input->next))
		ft_printf("%s\n", input->str);
	// while (input)
	// {
	// 	ft_printf("%s\n", input->str);
	// 	input = input->next;
	// }
	ft_printf("%s\n", "valid input");
	return (0);
}
