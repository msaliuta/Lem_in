/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prec_print_functs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:40:41 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/08 19:12:33 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	prec_print(t_pf_env *o, double d, char type, int k)
{
	if (k == 1)
	{
		ftoa_f(o, d, 0);
		prec_print_hp(d, o);
	}
	else if (k == 2)
	{
		check_form(o, d, type);
		prec_print_hp(d, o);
	}
	else if (k == 0)
	{
		ftoa_e(o, d, type, 0);
		prec_print_hp(d, o);
	}
}

void	print_prec_a(t_pf_env *o, double d, char type)
{
	ftoa_a(o, d, type);
	if (d < 0)
		o->ret += write(1, "-", 1);
	if (o->flmd.zero)
	{
		base_pre_print(o, type, 1);
		prec_width_print(o);
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
	}
	else if (o->flmd.minus)
		prec_print_hp(d, o);
	else
	{
		o->flmd.width -= 2;
		prec_width_print(o);
		base_pre_print(o, type, 1);
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
	}
	free(o->out);
	++o->i;
}

void	prec_print_hp(long double d, t_pf_env *o)
{
	if (o->flmd.minus)
	{
		if (d > 0 && (o->flmd.plus || o->flmd.space))
		{
			if (o->flmd.plus == 1)
				o->ret += write(o->fd, "+", 1);
			else
				write(o->fd, " ", 1);
		}
	}
	else
	{
		prec_width_print(o);
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
	}
	++o->i;
	free(o->out);
}
