/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:20 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:00 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	prrint_wchar_1(t_pf_env *o, char c)
{
	write(o->fd, &c, 1);
}

void	check_wchar(t_pf_env *o, wchar_t c)
{
	if (c <= 0x7F)
		prrint_wchar_1(o, c);
	else if (c <= 0x7FF)
	{
		prrint_wchar_1(o, (c >> 6) + 0xC0);
		prrint_wchar_1(o, (c & 0x3F) + 0x80);
	}
	else if (c <= 0xFFFF)
	{
		prrint_wchar_1(o, ((c >> 12) + 0xE0));
		prrint_wchar_1(o, ((c >> 6) & 0x3F) + 0x80);
		prrint_wchar_1(o, (c & 0x3F) + 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		prrint_wchar_1(o, (c >> 18) + 0xF0);
		prrint_wchar_1(o, ((c >> 12) & 0x3F) + 0x80);
		prrint_wchar_1(o, ((c >> 6) & 0x3F) + 0x80);
		prrint_wchar_1(o, (c & 0x3F) + 0x80);
	}
	++o->ret;
}

void	print_wchar(t_pf_env *o, wchar_t wc)
{
	if (o->flmd.minus)
	{
		check_wchar(o, wc);
		while (o->flmd.width-- > 1)
			o->ret += write(o->fd, " ", 1);
	}
	else
	{
		while (o->flmd.width-- > 1)
			if (o->flmd.zero)
				o->ret += write(o->fd, "0", 1);
			else
				o->ret += write(o->fd, " ", 1);
		check_wchar(o, wc);
	}
	++o->i;
}

void	wchar_init(t_pf_env *o, wchar_t *tmp)
{
	if (o->tag.tag)
	{
		va_copy(o->ap[0], o->ap[1]);
		while (--o->tag.pos >= 0)
			*tmp = va_arg(o->ap[0], wchar_t);
		return ;
	}
	*tmp = va_arg(o->ap[0], wchar_t);
}

void	process_wchar(t_pf_env *o, char type)
{
	wchar_t *ws;
	wchar_t wc;

	if (o->flmd.minus)
		o->flmd.zero = 0;
	if (type == 's' || type == 'S')
	{
		wstr_init(o, &ws);
		if (ws == NULL)
			return (str_for_print(o, 0));
		print_wstr(o, ws);
	}
	else if (type == 'c' || type == 'C')
	{
		wchar_init(o, &wc);
		if (wc == 0)
		{
			char_for_ptint(o, 0);
		}
		print_wchar(o, wc);
	}
}
