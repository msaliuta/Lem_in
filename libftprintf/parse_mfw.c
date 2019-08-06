/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_mfw.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 07:06:53 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:00 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_mfw(const char *restrict frmt, t_pf_env *o)
{
	int	i;
	int tmp;

	i = 0;
	o->flmd.space = 0;
	o->flmd.plus = 0;
	o->flmd.neg = 0;
	o->flmd.minus = 0;
	o->flmd.hash = 0;
	o->flmd.zero = 0;
	o->flmd.prec = -1;
	o->flmd.width = 0;
	if (INUM(frmt[o->i]))
	{
		tmp = ft_atoi(frmt + o->i);
		while (INUM(frmt[o->i + i]))
			i++;
		if (frmt[o->i + i] == '$')
		{
			o->tag.tag = 1;
			o->tag.pos = tmp;
			o->i += i + 1;
		}
	}
}

void	parse_size_spec(const char *restrict frmt, t_pf_env *o)
{
	if (frmt[o->i] == '%')
		process_percent(o);
	else if (CHECK_INT(frmt[o->i]) && o->mod != Z)
		process_int(o);
	else if (CHECK_UINT(frmt[o->i]) || (CHECK_INT(frmt[o->i]) && o->mod == Z))
		process_unsint(o, frmt[o->i]);
	else if (CHECK_CHR(frmt[o->i]) && o->mod != L)
		process_char(o, frmt[o->i]);
	else if (CHECK_LCHR(frmt[o->i]))
		process_char(o, frmt[o->i] + 32);
	else if ((CHECK_CHR(frmt[o->i]) && o->mod == L) ||
			CHECK_LCHR(frmt[o->i]))
		process_wchar(o, frmt[o->i]);
	else if (CHECK_PRC(frmt[o->i]) || CHECK_LPRC(frmt[o->i]))
		parse_prec(o, frmt[o->i]);
	else if (CHECK_HEX(frmt[o->i]) || CHECK_LHEX(frmt[o->i]))
		process_base(o, frmt[o->i]);
	else if (IN(frmt[o->i]))
		process_return(o);
	else if (frmt[o->i] == 'p' || frmt[o->i] == 'P')
		process_ptraddr(o, frmt[o->i]);
	else if (CHECK_BONUS(frmt[o->i]))
		process_nonprintable(o);
	else if (frmt[o->i] != '\0')
		print_invalid_spec(o, frmt[o->i]);
}

void	check_width(t_pf_env *o)
{
	o->flmd.width = va_arg(o->ap[0], int);
	if (o->flmd.width < 0)
	{
		o->flmd.width = -o->flmd.width;
		o->flmd.minus = 1;
	}
}

void	check_prec(const char *restrict frmt, t_pf_env *o)
{
	if (o->flmd.prec >= 0)
	{
		++o->i;
		return ;
	}
	if (frmt[o->i] == '.' && frmt[o->i + 1] == '*')
	{
		o->flmd.prec = va_arg(o->ap[0], int);
		o->i += 2;
	}
	else if (frmt[o->i] == '.')
	{
		++o->i;
		o->flmd.prec = ft_atoi(frmt + o->i);
		while (INUM(frmt[o->i]))
			++o->i;
	}
}

void	parse_prec(t_pf_env *o, char type)
{
	long double	ld;
	double		d;

	if (o->mod == L1)
	{
		init_long_double(o, &ld);
		if (ld != ld || (ld * 2 == ld && ld != 0))
			return (nan_inf(o, type, ld));
	}
	else
	{
		init_double_argm(o, &d);
		if (d != d || (d * 2 == d && d != 0))
			return (nan_inf(o, type, d));
		ld = (long double)d;
	}
	if (type == 'e' || type == 'E')
		return (prec_print(o, ld, type, 0));
	if (type == 'f' || type == 'F')
		return (prec_print(o, ld, '0', 1));
	if (type == 'g' || type == 'G')
		return (prec_print(o, ld, type, 2));
	if (type == 'a' || type == 'A')
		return (print_prec_a(o, ld, type));
}
