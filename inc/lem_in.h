/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:47:41 by msaliuta          #+#    #+#             */
/*   Updated: 2019/08/14 15:08:43 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	LEM_IN_H
# define LEM_IN_H

# include "../libftprintf/includes/libft.h"

typedef struct		s_lemin
{
	char			*str;
	struct	s_lemin	*next;
}					t_lemin;

typedef struct		s_node
{
	int				stfn;
	int				width;
	int				used;
	int				x;
	int				y;
	char			*title;
	struct	s_cnct	*next;
}					t_node;

#endif
