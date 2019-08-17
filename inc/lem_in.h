/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:47:41 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/17 20:57:43 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LEM_IN_H
# define LEM_IN_H

# include "../libftprintf/includes/libft.h"

// typedef struct		s_lemin
// {
// 	char			*str;
// 	struct	s_lemin	*next;
// }					t_lemin;

// typedef struct		s_node
// {
// 	int				stfn;
// 	int				width;
// 	int				used;
// 	int				x;
// 	int				y;
// 	char			*title;
// 	struct	s_cnct	*next;
// }					t_node;

typedef	struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				startend;
	int				wth;
	int				taken;
	int				used;
	struct s_room	*next;
}					t_room;

typedef	struct		s_write
{
	char			*str;
	struct s_write	*next;
}					t_write;

typedef	struct		s_path
{
	int				**path;
	int				**node;
	int				*len;
	int				step;
	int				path_n;
}					t_path;

int		check_args(int ac, char **av, int *arg_used);
void	read_n_stock(int *ant_n, t_room **room, t_write **str);
void	stock_room(char *line, t_room **begin, int *startend, int *error);
int		valid_digit(char *line);
int		room_form_is_valid(char *str);
int		extract_room_x(char *str, int *error);
char	*extract_room_name(char *str);
int		extract_room_y(char *str, int *error);
int		room_already_exist(t_room **begin, t_room *new, t_room **end);
int		link_form_is_valid(char *str);
int		ft_isalnum(int c);
void	save_line(char *line, int *error, t_write **str);
void	stock_to_write(char *line, t_write **begin);
int		command_is_valid(char *str);
void	set_startend(char *line, int *startend, int *error);
void	free_lst_write(t_write **begin);
void	free_lst_room(t_room **begin);
char	*ft_strndup(const char *s, size_t n);
void	coord_is_valid(char *coord, int *error);
long	ft_atol(const char *str);

#endif
