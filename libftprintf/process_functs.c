/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_functs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:22 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:00 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	process_base(t_pf_env *o, char type)
{
	long			tmp;
	unsigned long	val;

	val = 0;
	init_long_argm(o, &tmp);
	if (type == 'O' || o->mod == Z || o->mod == T ||
		o->mod == J || o->mod == L || o->mod == LL)
		val = (unsigned long)tmp;
	else if (o->mod == HH)
		val = (unsigned char)tmp;
	else if (o->mod == H)
		val = (unsigned short)tmp;
	else if (o->mod == NOMOD)
		val = (unsigned int)tmp;
	if (type == 'b' || type == 'B')
		o->out = ft_ultoa_base(val, 2);
	if (type == 'o' || type == 'O')
		o->out = ft_ultoa_base(val, 8);
	if (type == 'x' || type == 'X')
		o->out = ft_ultoa_base(val, 16);
	if (type == 'b' || type == 'o' || type == 'x')
		ft_strlower(o->out);
	o->flmd.minus == 1 ? o->flmd.zero = 0 : 0;
	base_print(o, type, (long)val);
}

void	process_return(t_pf_env *o)
{
	int	*tmp;

	if (o->tag.tag)
	{
		va_copy(o->ap[0], o->ap[1]);
		while (--o->tag.pos >= 0)
			tmp = va_arg(o->ap[0], int *);
	}
	tmp = va_arg(o->ap[0], int *);
	*tmp = o->ret;
	++o->i;
}

void	process_ptraddr(t_pf_env *o, char type)
{
	long			tmp;
	unsigned long	addr;

	init_long_argm(o, &tmp);
	addr = (unsigned long)tmp;
	if (o->flmd.prec == 0)
		o->out = ft_strdup("\0");
	else
		o->out = ft_ltoa_base(addr, 16);
	print_ptraddr(o, type);
}

void	process_nonprintable(t_pf_env *o)
{
	char	*tmp;
	int		i;

	init_str_arg(o, &tmp);
	i = -1;
	while (++i < o->flmd.width)
	{
		if (tmp[i] >= 0 && tmp[i] <= 10)
			print_first_dec(o, tmp[i]);
		else if (tmp[i] >= 11 && tmp[i] <= 20)
			print_second_dec(o, tmp[i]);
		else if (tmp[i] >= 21 && tmp[i] <= 31)
			print_pf_thirtd_dec(o, tmp[i]);
		++o->ret;
	}
	++o->i;
}

void	process_percent(t_pf_env *o)
{
	if (o->flmd.minus)
	{
		o->ret += write(o->fd, "%", 1);
		while (o->flmd.width-- > 1)
			o->ret += write(o->fd, " ", 1);
	}
	else
	{
		while (o->flmd.width-- > 1)
		{
			if (o->flmd.zero)
				o->ret += write(o->fd, "0", 1);
			else
				o->ret += write(o->fd, " ", 1);
		}
		o->ret += write(o->fd, "%", 1);
	}
	++o->i;
}
