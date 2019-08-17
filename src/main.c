/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:44:43 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/17 20:52:05 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

long	ft_atol(const char *str)
{
	long int	i;
	long int	res;
	long int	neg;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\r' || str[i] == '\v'
			|| str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + ((str[i++] - '0') * neg);
	return (res);
}

void	coord_is_valid(char *coord, int *error)
{
	if (ft_atol(coord) > 2147483647 || ft_atol(coord) < -2147483648
			|| ft_strlen(coord) > 11)
	{
		*error = 1;
		write(2, "Invalid Room\nUsage : <name> <int> <int>\n", 40);
	}
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*dst;

	i = 0;
	if (!(dst = (char*)malloc(sizeof(char) * (n + 1))))
		return (0);
	while (s[i] && i < n)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

void	free_lst_room(t_room **begin)
{
	t_room	*current;
	t_room	*before;

	current = 0;
	before = 0;
	if (begin && *begin)
	{
		before = *begin;
		current = before->next;
		*begin = 0;
		before->next = 0;
		ft_strdel(&(before->name));
		free(before);
		while (current)
		{
			before = current;
			current = current->next;
			before->next = 0;
			ft_strdel(&(before->name));
			free(before);
			before = 0;
		}
	}
}

void	free_lst_write(t_write **begin)
{
	t_write	*current;
	t_write	*before;

	current = 0;
	before = 0;
	if (begin && *begin)
	{
		before = *begin;
		current = before->next;
		*begin = 0;
		before->next = 0;
		ft_strdel(&(before->str));
		free(before);
		while (current)
		{
			before = current;
			current = current->next;
			before->next = 0;
			ft_strdel(&(before->str));
			free(before);
			before = 0;
		}
	}
}

void	set_startend(char *line, int *startend, int *error)
{
	if (!(ft_strcmp("##start", line)) && *startend == 0)
		*startend = 1;
	else if (!(ft_strcmp("##end", line)) && *startend == 0)
		*startend = 2;
	else
		*error = 1;
}

int		command_is_valid(char *str)
{
	if (!(ft_strcmp("##start", str)) || !(ft_strcmp("##end", str)))
		return (1);
	return (0);
}

void	stock_to_write(char *line, t_write **begin)
{
	t_write	*new;
	t_write	*current;

	if (!(new = (t_write*)malloc(sizeof(t_write) * 1)))
		exit(0);
	new->str = ft_strdup(line);
	new->next = 0;
	if (!(*begin))
		*begin = new;
	else if (new)
	{
		current = *begin;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	save_line(char *line, int *error, t_write **str)
{
	stock_to_write(line, str);
	*error = 1;
}

int		ft_isalnum(int c)
{
	if (ft_isalpha(c) == 1 || ft_isdigit(c) == 1)
		return (1);
	return (0);
}

int		link_form_is_valid(char *str)
{
	int	i;

	if (!(str && str[0]) || str[0] == 'L' || str[0] == '#')
		return (0);
	i = (int)(ft_strlen(str)) - 1;
	while (i >= 0 && (ft_isalnum(str[i]) || str[i] == '_'))
		i--;
	if (i < 1 || str[i] != '-' || (str[i + 1] && str[i + 1] == 'L'))
		return (0);
	i--;
	while (i >= 0 && (ft_isalnum(str[i]) || str[i] == '_'))
		i--;
	if (i != -1)
		return (0);
	return (1);
}

int		room_already_exist(t_room **begin, t_room *new, t_room **end)
{
	t_room	*current;

	if (!(begin && *begin))
		return (0);
	current = *begin;
	while (current)
	{
		if (current->next == 0)
			*end = current;
		if (!(ft_strcmp(current->name, new->name)))
			return (1);
		else if (current->x == new->x && current->y == new->y)
			return (1);
		else if (new->startend != 0 && new->startend == current->startend)
			return (1);
		current = current->next;
	}
	return (0);
}

int		extract_room_y(char *str, int *error)
{
	int		y;
	char	*y_str;
	size_t	i;
	size_t	len;

	y = 0;
	i = 0;
	len = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	i++;
	while (ft_isdigit(str[i]) || str[i] == '+' || str[i] == '-')
		i++;
	i++;
	while (ft_isdigit(str[i + len]) || str[i + len] == '+'
			|| str[i + len] == '-')
		len++;
	if (!(y_str = ft_strndup(str + i, (size_t)len)))
		exit(0);
	coord_is_valid(y_str, error);
	y = ft_atoi(y_str);
	free(y_str);
	return (y);
}

char	*extract_room_name(char *str)
{
	char	*name;
	int		i;

	name = 0;
	i = 0;
	if (!(str))
		return (0);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	if (!(name = ft_strndup(str, (size_t)i)))
		exit(0);
	return (name);
}

int		extract_room_x(char *str, int *error)
{
	int		x;
	char	*x_str;
	size_t	i;
	size_t	len;

	x = 0;
	i = 0;
	len = 0;
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	i++;
	while (ft_isdigit(str[i + len]) || str[i + len] == '+'
			|| str[i + len] == '-')
		len++;
	if (!(x_str = ft_strndup(str + i, (size_t)len)))
		exit(0);
	coord_is_valid(x_str, error);
	x = ft_atoi(x_str);
	free(x_str);
	return (x);
}

int		room_form_is_valid(char *str)
{
	int	i;

	if (!(str && str[0]) || str[0] == 'L' || str[0] == '#')
		return (0);
	i = (int)(ft_strlen(str)) - 1;
	while (i >= 0 && ft_isdigit(str[i]))
		i--;
	if (i >= 0 && (str[i] == '+' || str[i] == '-'))
		i--;
	if (i < 3 || str[i] != ' ' || !(ft_isdigit(str[i - 1])))
		return (0);
	i--;
	while (i >= 0 && ft_isdigit(str[i]))
		i--;
	if (i >= 0 && (str[i] == '+' || str[i] == '-'))
		i--;
	if (i < 1 || str[i] != ' ')
		return (0);
	i--;
	while (i >= 0 && (ft_isalnum(str[i]) || str[i] == '_'))
		i--;
	if (i != -1)
		return (0);
	return (1);
}

int		valid_digit(char *line)
{
	int	i;

	i = -1;
	if (!(line[0]))
		return (0);
	while (line[++i])
		if (!(ft_isdigit(line[i])) && !(i == 0 && line[i] == '-'))
			return (0);
	if (ft_atol(line) > 2147483647 || ft_atol(line) < 1 || ft_strlen(line) > 11)
	{
		write(2, "Invalid number of ants\nUsage : <int > 0>\n", 41);
		return (0);
	}
	return (1);
}

void	stock_room(char *line, t_room **begin, int *startend, int *error)
{
	t_room	*new;
	t_room	*end;

	if (!(new = (t_room*)malloc(sizeof(t_room) * 1)))
		exit(0);
	new->name = extract_room_name(line);
	new->x = extract_room_x(line, error);
	new->y = extract_room_y(line, error);
	new->startend = *startend;
	*startend = 0;
	new->next = 0;
	if (room_already_exist(begin, new, &end) || *error == 1)
	{
		free_lst_room(&new);
		*error = 1;
	}
	else if (!(*begin))
		*begin = new;
	else
		end->next = new;
}

void	read_n_stock(int *ant_n, t_room **room, t_write **str)
{
	char	*line;
	int		startend;
	int		error;
	int		n;

	n = 0;
	line = 0;
	startend = 0;
	error = 0;
	while (get_next_line(0, &line) > 0)
	{
		if (valid_digit(line) && (*ant_n <= 0) && !(*room))
			*ant_n = ft_atoi(line);
		else if (room_form_is_valid(line) && (*ant_n > 0))
			stock_room(line, room, &startend, &error);
		else if (link_form_is_valid(line) && (*ant_n > 0) && startend == 0)
			save_line(line, &error, str);
		else if ((n = command_is_valid(line)) && (*ant_n > 0))
			set_startend(line, &startend, &error);
		else if (line[0] != '#')
			error = 1;
		if (error)
			break ;
		stock_to_write(line, str);
		ft_strdel(&line);
	}
	ft_strdel(&line);
}

int		check_args(int ac, char **av, int *arg_used)
{
	if (ac == 1)
		return (1);
	/*if (ac > 2)
	{
		ft_printf("Too many arguments\n");
		return (0);
	}*/
	if (ft_strcmp(av[1], "-h") == 0)
	{
		ft_printf("Usage: ./lem-in -argument (only one arg or none) < map\n\n");
		ft_printf("ARGUMENT:\t\t\t\tMAP PROTOTYPE:\n");
		ft_printf("-h : help for command\t\t\t\tlink: <name1>-<name2>\n");
		return (0);
	}
	else
	{
		ft_printf("Wrong Argument\n");
		arg_used = 0;
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	int		ant_n;
	t_room	*roombeg;
	t_write	*str;
	int		arg_used;

	ant_n = 0;
	roombeg = 0;
	str = 0;
	arg_used = 0;
	if (!(check_args(ac, av, &arg_used)))
		return (0);
	read_n_stock(&ant_n, &roombeg, &str);
	if (!roombeg)
	 	write(1, "ERROR", 6);
	free_lst_write(&str);
	free_lst_room(&roombeg);
	return (0);
}

/*int		parse(int *n)
{
	char	*line;
	int		sf;
	int		err;
	int		i;

	i = 0;
	line = 0;
	sf = 0;
	err = 0;

	while (get_next_line(0, &line) > 0)
	{
		if (n <= 0)
			*n = ft_atoi(line);
		else if (line[0] != '#')
			err = 1;
		if (err)
			return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	int		n;
	int		i;
	///t_node	*stock;
	//t_lemin *str;
	char	*str;

	str = av[1];
	//str = 0;
	if (ac == 1)
		return (1);
	if (ac > 2)
	{
		ft_printf("not correct input");
		return (0);
	}
	n = 0;
	i = 1;
	//stock = 0;
	i = parse(&n);
	if (i == 0)
		ft_printf("error");
	return (0);
}*/
