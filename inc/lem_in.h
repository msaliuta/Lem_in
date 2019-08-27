/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:47:41 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/28 00:00:21 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LEM_IN_H
# define LEM_IN_H

# include "../libftprintf/includes/libft.h"

typedef struct	s_room		t_room;
typedef struct	s_array		t_array;
typedef	struct	s_lem_in	t_struct;
typedef struct	s_input		t_input;

struct	s_room
{
	t_array			*links;
	t_room			*parent;
	t_room			*next;
	char			*name;
	int				x;
	int				y;
	short			dst_from_end;
	unsigned int	full_of_ants;
	bool			visited;
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
	int				ants_at_the_end;
	int				ants_left_at_start;
	unsigned short	count_of_rooms;
	bool			space;
};

#endif
