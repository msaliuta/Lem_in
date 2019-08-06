/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_functs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:14 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:00 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	char_for_ptint(t_pf_env *o, int n)
{
	if (n == 1)
	{
		while (o->flmd.width-- > 1)
		{
			if (o->flmd.zero == 1)
				o->ret += write(o->fd, "0", 1);
			else
				o->ret += write(o->fd, " ", 1);
		}
	}
	else
	{
		while (o->flmd.width-- > 1)
		{
			if (o->flmd.zero == 1)
				o->ret += write(o->fd, "0", 1);
			else
				o->ret += write(o->fd, " ", 1);
		}
		++o->i;
	}
}

void	process_char(t_pf_env *o, char type)
{
	char	*stmp;
	int		ctmp;

	if (o->flmd.minus)
		o->flmd.zero = 0;
	if (type == 's')
	{
		init_str_arg(o, &stmp);
		if (stmp == NULL)
			return (str_for_print(o, 0));
		else if (o->flmd.prec)
			o->out = ft_strdup((char*)stmp);
		else
			o->out = ft_strdup("\0");
		str_print(o);
	}
	else if (type == 'c')
	{
		init_char_arg(o, &ctmp);
		char_print(o, ctmp);
	}
}

void	init_char_arg(t_pf_env *o, int *tmp)
{
	if (o->tag.tag)
	{
		va_copy(o->ap[0], o->ap[1]);
		while (--o->tag.pos >= 0)
			*tmp = va_arg(o->ap[0], int);
		return ;
	}
	*tmp = va_arg(o->ap[0], int);
}

void	char_print(t_pf_env *o, char c)
{
	if (o->flmd.minus)
	{
		o->ret += write(o->fd, &c, 1);
		char_for_ptint(o, 1);
	}
	else
	{
		char_for_ptint(o, 1);
		o->ret += write(o->fd, &c, 1);
	}
	++o->i;
}
