/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstr_functs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:21 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:00 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_wstr(t_pf_env *o, wchar_t c)
{
	if (c <= 0x7F)
		prrint_wstr_1(o, c);
	else if (c <= 0x7FF)
	{
		prrint_wstr_1(o, (c >> 6) + 0xC0);
		prrint_wstr_1(o, (c & 0x3F) + 0x80);
	}
	else if (c <= 0xFFFF)
	{
		prrint_wstr_1(o, ((c >> 12) + 0xE0));
		prrint_wstr_1(o, ((c >> 6) & 0x3F) + 0x80);
		prrint_wstr_1(o, (c & 0x3F) + 0x80);
	}
	else if (c <= 0x10FFFF)
	{
		prrint_wstr_1(o, (c >> 18) + 0xF0);
		prrint_wstr_1(o, ((c >> 12) & 0x3F) + 0x80);
		prrint_wstr_1(o, ((c >> 6) & 0x3F) + 0x80);
		prrint_wstr_1(o, (c & 0x3F) + 0x80);
	}
}

int		get_wstr_len(wchar_t *wchr)
{
	int i;
	int len;

	i = -1;
	len = 0;
	while (wchr[++i] != 0)
	{
		if (wchr[i] <= 0x7F)
			len++;
		else if (wchr[i] <= 0x7FF)
			len += 2;
		else if (wchr[i] <= 0xFFFF)
			len += 3;
		else if (wchr[i] <= 0x10FFFF)
			len += 4;
	}
	return (len);
}

void	wstr_min_print(t_pf_env *o, wchar_t *wchr, int len)
{
	int i;

	i = -1;
	if (o->flmd.prec >= 0)
	{
		while (wchr[++i] != 0 && i < o->flmd.prec)
			check_wstr(o, wchr[i]);
	}
	else
	{
		while (wchr[++i] != 0)
			check_wstr(o, wchr[i]);
	}
	while (o->flmd.width-- > len)
		if (o->flmd.zero == 1)
			o->ret = write(o->fd, "0", 1);
		else
			o->ret = write(o->fd, " ", 1);
}

void	wstr_init(t_pf_env *o, wchar_t **tmp)
{
	if (o->tag.tag)
	{
		va_copy(o->ap[0], o->ap[1]);
		while (--o->tag.pos >= 0)
			*tmp = va_arg(o->ap[0], wchar_t *);
		return ;
	}
	*tmp = va_arg(o->ap[0], wchar_t *);
}

void	print_wstr(t_pf_env *o, wchar_t *wchr)
{
	int i;
	int len;

	i = -1;
	if (o->flmd.prec < 0)
		len = get_wstr_len(wchr);
	else
		len = o->flmd.prec;
	if (o->flmd.minus)
		wstr_min_print(o, wchr, len);
	else
	{
		while (o->flmd.width-- > len)
			o->ret += (o->flmd.zero == 1 ?
			write(o->fd, "0", 1) : write(o->fd, " ", 1));
		if (o->flmd.prec >= 0)
			while (wchr[++i] != 0 && i * 4 < o->flmd.prec)
				check_wstr(o, wchr[i]);
		else
			while (wchr[++i] != 0)
				check_wstr(o, wchr[i]);
	}
	++o->i;
}
