/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:15 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/08 19:12:33 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	digit_sign_print(t_pf_env *o)
{
	if (o->flmd.plus || o->flmd.space)
	{
		if (o->flmd.plus == 1)
			o->ret += write(o->fd, "+", 1);
		else
			o->ret += write(o->fd, " ", 1);
	}
	else if (o->flmd.neg)
		o->ret += write(o->fd, "-", 1);
}

void	digit_print(t_pf_env *o)
{
	process_dgt_prec(o);
	if (o->flmd.zero)
	{
		digit_sign_print(o);
		digit_width_print(o);
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
	}
	else if (o->flmd.minus)
	{
		digit_sign_print(o);
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
		digit_width_print(o);
	}
	else
	{
		digit_width_print(o);
		digit_sign_print(o);
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
	}
	++o->i;
	free(o->out);
}

void	base_pre_print(t_pf_env *o, char type, long val)
{
	if (o->flmd.hash && o->out[0] != '\0' && val != 0)
		bpp_check(o, type, 1);
	else if ((type == 'o' || type == 'O') && o->flmd.hash && o->flmd.prec >= 0)
		o->ret += write(o->fd, "0", 1);
	else if (type == 'a' || type == 'A')
	{
		if (o->flmd.plus || o->flmd.space)
		{
			bpp_check(o, type, 2);
		}
		if (type == 'a')
		{
			o->ret += type;
			write(o->fd, "0x", 2);
		}
		else
		{
			o->ret += type;
			write(o->fd, "0X", 2);
		}
		o->flmd.width -= 2;
	}
}

void	bpp_check(t_pf_env *o, char type, int n)
{
	if (n == 1)
	{
		if (type == 'o' || type == 'O')
			o->ret += write(o->fd, "0", 1);
		if (type == 'x')
			o->ret += write(o->fd, "0x", 2);
		if (type == 'X')
			o->ret += write(o->fd, "0X", 2);
		if (type == 'a' || type == 'A')
			o->flmd.width -= 2;
	}
	else
	{
		if (o->flmd.space)
		{
			o->ret += o->flmd.space;
			write(1, " ", 1);
		}
		else
		{
			o->ret += o->flmd.space;
			write(1, "+", 1);
		}
	}
}

void	base_print(t_pf_env *o, char type, long val)
{
	check_prec_base(o, type);
	if (o->flmd.zero)
	{
		base_pre_print(o, type, val);
		base_width_print(o, type);
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
	}
	else if (o->flmd.minus)
	{
		base_pre_print(o, type, val);
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
		base_width_print(o, type);
	}
	else
	{
		base_width_print(o, type);
		base_pre_print(o, type, val);
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
	}
	++o->i;
	free(o->out);
}
