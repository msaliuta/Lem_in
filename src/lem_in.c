#include "lem_in.h"

bool	expandable_arr(t_array **old)
{
	int	i;
	t_room	**tmp_links;

	i = -1;
	tmp_links = (*old)->links;
	if ((*old)->limit < 100)
		(*old)->limit = (*old)->limit * 3;
	else
		(*old)->limit = (*old)->limit * 2;
	if (! ((*old)->links = ft_memalloc(sizeof(t_room *) * (*old)->limit)))
	{
		ft_printf("error");
		exit(EXIT_FAILURE);
	}
	while (++i < (*old)->size && tmp_links)
		(*old)->links[i] = tmp_links[i];
	(*old)->links[++i] = NULL;
	free(tmp_links);
	return (true);
}

void	is_room_exist(t_room **tmp, char *name_from)
{
	while ((*tmp) && !ft_strequ((*tmp)->name, name_from))
		if ((*tmp)->next)
			*tmp = (*tmp)->next;
		else
		{
			ft_printf("error");
			exit(EXIT_FAILURE);
		}
	if (!(*tmp)->links)
	{
		ft_printf("error");
		exit(EXIT_FAILURE);
	}
}

void	set_link(t_room *lst, char *line)
{
	int	i;
	t_room	*tmp;
	t_room	*tmp_2;
	char	name_from[50];
	char	*name_to;

	i = 0;
	tmp = lst;
	tmp_2 = lst;
	name_to = ft_strdup(ft_strchr(line, '-') + 1);
	ft_memcpy(name_from, line, (int)(ft_strchr(line, '-') - line));
	name_from[(int)(ft_strchr(line, '-') - line)] = '\0';
	is_room_exist(&tmp, name_from);
	is_room_exist(&tmp_2, name_to);
	while (tmp->links->links[i])
	{
		++i == tmp->links->limit ? expandable_arr(&tmp->links) : 0;
	}
	tmp->links->links[i] = tmp_2;
	tmp->links->size++;
	tmp->links->links[++i] = NULL;
	i = 0;
	while (tmp_2->links->links[i])
	{
		++i == tmp_2->links->limit ? expandable_arr(&tmp_2->links) : 0;
	}
	tmp_2->links->links[i] = tmp;
	tmp_2->links->size++;
	tmp_2->links->links[++i] = NULL;
	free(name_to);
}

t_array	*new_array(int def_size)
{
	int	i;
	t_array	*new_arr;

	i = 0;
	if (!(new_arr = ft_memalloc(sizeof(t_array))))
	{
		ft_printf("%s", "error");
		exit(EXIT_FAILURE);
	}
	new_arr->size = 0;
	new_arr->limit = def_size - 1;
	if (!(new_arr->links = ft_memalloc(sizeof(t_room *) * def_size)))
	{
		ft_printf("%s", "error");
		exit(EXIT_FAILURE);
	}
	while (i < def_size)
		new_arr->links[i++] = NULL;
	return (new_arr);
}

t_room	*new_room(char *line)
{
	t_room		*tmp;
	const int	n = ft_strchr(line, ' ') - line;

	if (!(tmp = ft_memalloc(sizeof(t_room))))
	{
		ft_printf("%s\n", "error");
		exit(EXIT_FAILURE);
	}
	tmp->name = ft_memalloc(sizeof(char) * (n + 1));
	ft_memcpy(tmp->name, line, n);
	line = ft_strchr(line, ' ') + 1;
	tmp->x = ft_atoi(line);
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
	char		name[256];

	if (tmp->x == atoi(i) && tmp->y == atoi(j))
	{
		ft_printf("error");
		exit(EXIT_FAILURE);
	}
	ft_bzero(name, 256);
	ft_memcpy(name, line, i - line - 1);
	if (ft_strequ(name, tmp->name))
	{
		ft_printf("error");
		exit(EXIT_FAILURE);
	}
	return (true);
}

bool	set_room(t_room **rooms, t_struct *lemin, char *line, int n)
{
	t_room	*tmp;

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
	{
		ft_printf("%s\n", "error");
		exit (EXIT_FAILURE);
	}
	printf("%d%d%s\n", tmp->x, tmp->y, tmp->name);
	n == 1 ? lemin->start = tmp : 0;
	n == 2 ? lemin->end = tmp : 0;
	return (true);
}

int	check_ants(char *line)
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

void	parse_l(t_room *rooms, t_struct *lemin, int err)
{
	int	i;
	char	*line;

	line = 0;
	lemin->dst = 0;
	lemin->count_of_rooms = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (lemin->ants == 0 && check_ants(line))
			lemin->ants = ft_atoi(line);
		else if (line[0] == '#' && i != 0)
			err = 1;
		else if (line[0] == '#' && line[1] == '#' && i == 0 && lemin->ants > 0)
		{
			ft_strequ(line, "##start") ? (i = 1) : 0;
			ft_strequ(line, "##end") ? (i = 2) : 0;
		}
		else if (ft_chr_count(line, ' ') == 2 &&
			line[0] != 'L' && lemin->ants > 0)
			set_room(&rooms, lemin, line, i) ? (i = 0) : 0;
		else if (ft_chr_count(line, '-') && line[0] != '#')
			set_link(rooms, line);
		else if (line[0] != '#')
			err = 1;
		if (err == 1)
		{
			ft_printf("%s\n", "error");
			break ;
		}
		ft_strdel(&line);
	}
	if (!lemin->start || !lemin->end)
	{
		ft_printf("error");
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av)
{
	//t_array		*ways;
	t_room		*rooms;
	t_struct	*lemin;
	int		err;

	err = 0;
	lemin = ft_memalloc(sizeof(t_struct));
	rooms = ft_memalloc(sizeof(t_room));
	if (ac > 2 || !av)
		ft_printf("%s\n", "error");
	parse_l(rooms, lemin, err);
	if (err == 1)
	{
		printf("%s\n", "error");
		return (0);
	}
	return (0);
}
