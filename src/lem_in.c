/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:27:19 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/29 15:32:37 by msaliuta         ###   ########.fr       */
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
	tmp->lvl = -1;
	tmp->links = new_array(4);
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
	free(name);
	return (true);
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

void	parse_l(t_room **rooms, t_struct *lemin, t_input *input)
{
	int		i;
	char	*line;

	i = 0;
	while (get_next_line(0, &line) > 0)
	{
		input->next = save_input(line);
		input = input->next;
		if (lemin->ants == 0 && check_ants(line))
			lemin->ants = ft_atoi(line);
		else if (line[0] == '#' && line[1] == '#' && i == 0 && lemin->ants)
		{
			ft_strequ(line, "##start") ? (i = 1) : 0;
			ft_strequ(line, "##end") ? (i = 2) : 0;
		}
		else if (line[0] == '#')
			continue ;
		else if (ft_chr_count(line, ' ') == 2 && *line != 'L' && lemin->ants)
			set_room(rooms, lemin, line, i) ? (i = 0) : 0;
		else if (ft_chr_count(line, '-') && line[0] != '#' && i == 0)
			set_link(lemin, *rooms, line) && (lemin->links = 1);
		else
			terminate("Input invalid");
	}
}

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
