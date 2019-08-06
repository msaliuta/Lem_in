/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_functs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:11 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:00 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_long_argm(t_pf_env *o, long *tmp)
{
	if (o->tag.tag)
	{
		va_copy(o->ap[0], o->ap[1]);
		while (--o->tag.pos >= 0)
			*tmp = va_arg(o->ap[0], long);
		return ;
	}
	*tmp = va_arg(o->ap[0], long);
}

void	process_int(t_pf_env *o)
{
	long tmp;
	long i;

	init_long_argm(o, &tmp);
	i = (long long)tmp;
	if (o->flmd.minus == 1)
		o->flmd.zero = 0;
	if (o->flmd.prec >= 0)
		o->flmd.zero = 0;
	if (tmp == LLONG_MIN || tmp == LONG_MIN)
		o->out = ft_strdup("-9223372036854775808");
	else if (o->mod == Z)
		o->out = ft_itoa((size_t)i);
	else if (o->mod == HH)
		o->out = ft_itoa((char)i);
	else if (o->mod == H)
		o->out = ft_itoa((short)i);
	else if (o->mod == NOMOD)
		o->out = ft_itoa((int)i);
	else if (o->mod == L || o->mod == T ||
			o->mod == LL || o->mod == J)
		o->out = ft_ltoa((long)i);
	else if (o->mod == L1)
		o->out = ft_itoa((unsigned long)i);
	digit_print(o);
}

void	init_double_argm(t_pf_env *o, double *tmp)
{
	if (o->tag.tag)
	{
		va_copy(o->ap[0], o->ap[1]);
		while (--o->tag.pos >= 0)
			*tmp = va_arg(o->ap[0], double);
		return ;
	}
	*tmp = va_arg(o->ap[0], double);
}

void	process_unsint(t_pf_env *o, char type)
{
	long tmp;

	o->flmd.space = 0;
	o->flmd.plus = 0;
	init_long_argm(o, &tmp);
	if (tmp == LLONG_MIN || tmp == LONG_MIN)
		o->out = ft_strdup("-9223372036854775808");
	else if (type == 'D' || type == 'U' || o->mod == L ||
			o->mod == T || o->mod == J || o->mod == LL
			|| o->mod == L1)
		o->out = ft_ultoa((unsigned long)tmp);
	else if (o->mod == Z)
		o->out = ft_ltoa((long)tmp);
	else if (o->mod == H)
		o->out = ft_ltoa((unsigned short)tmp);
	else if (o->mod == HH)
		o->out = ft_ultoa((unsigned char)tmp);
	else if (o->mod == NOMOD && type != 'U')
		o->out = ft_ultoa((unsigned int)tmp);
	digit_print(o);
}
