/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:47:41 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/29 15:32:41 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libftprintf/includes/libft.h"

typedef struct s_room		t_room;
typedef struct s_array		t_array;
typedef	struct s_lem_in		t_struct;
typedef struct s_input		t_input;

struct	s_room
{
	t_array		*links;
	t_room		*parent;
	t_room		*next;
	char		*name;
	int			x;
	int			y;
	short		lvl;
	int			ants;
};

struct	s_array
{
	t_room			**links;
	unsigned short	limit;
	unsigned short	size;
};

struct	s_input
{
	t_input			*next;
	char			*str;
};

struct	s_lem_in
{
	t_room			*start;
	t_room			*end;
	bool			links;
	int				ants;
	int				dst;
	int				ants_left;
	unsigned short	count_of_rooms;
	int				n_path;
};

/*
**algo_start.s
*/

void	bfs_run(t_room *rooms, t_array *paths, t_struct *lemin);
bool	path_find(t_struct *lemin);
void	path_create(t_struct *lemin, t_array **paths);
void	zero(t_room *rooms);
void	block(int n_path, t_array *paths);

/*
**help_functs.c
*/

int		display_man(void);
void	free_paths(int n_path, t_array *paths);
void	bfs(t_room **queue, t_room *curr, int *end);
int		ft_min(int a, int b);
void	print_input(t_input *input);

/*
**
*/

void	go_ants(t_struct *lemin, t_array *paths);
void	step(int **ants, t_array *paths, t_struct *lemin);
int		count_sum_of_paths(t_array *paths, int n);
int		find_free_path(int n_path, t_array *paths);
void	display_paths(char *start, int n_path, t_array *paths);
void	parse_l(t_room **rooms, t_struct *lemin, t_input *input);
t_input	*save_input(char *line);
int		check_ants(char *line);
bool	set_room(t_room **rooms, t_struct *lemin, char *line, int n);
bool	check_roomd(char *line, t_room *tmp);
t_room	*new_room(char *line);
int		check_nbr(char *line);
t_array	*new_array(int def_size);
int		set_link(t_struct *lemin, t_room *lst, char *line);
int		is_room_exist(t_room **r_a, t_room **r_b, char **n_a, char **n_b);
bool	expandable_arr(t_array **old);
void	terminate(char *message);

#endif
