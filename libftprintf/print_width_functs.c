/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_width_functs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:14 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:00 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	base_width_print(t_pf_env *o, char type)
{
	int	i;
	int len;

	i = -1;
	len = ft_strlen(o->out);
	if (o->flmd.hash && (o->out[0] != '\0' && o->out[0] != '0'))
		bpw_check(o, type);
	if (o->flmd.prec >= 0)
	{
		while (o->flmd.width > o->flmd.prec + ++i && o->flmd.width > len + i)
			o->ret += write(o->fd, " ", 1);
		while (o->flmd.width > len + i++)
			o->ret += write(o->fd, "0", 1);
	}
	else
	{
		while (o->flmd.width > len + ++i)
			if (o->flmd.zero == 1)
				o->ret += write(o->fd, "0", 1);
			else
				o->ret += write(o->fd, " ", 1);
	}
}

void	bpw_check(t_pf_env *o, char type)
{
	if (type == 'o' || type == 'O')
		o->flmd.width -= 1;
	else
		o->flmd.width -= 0;
	if (type == 'x' || type == 'X')
		o->flmd.width -= 2;
	else
		o->flmd.width -= 0;
}

void	check_prec_base(t_pf_env *o, char type)
{
	char	*tmp;
	char	*res;
	int		len;
	int		i;

	len = (int)ft_strlen(o->out);
	if (o->flmd.prec == 0 && o->out[0] == '0')
		o->out[0] = '\0';
	else if (o->flmd.prec > len)
	{
		if ((type == 'o' || type == 'O') && o->flmd.hash)
			o->flmd.prec--;
		i = o->flmd.prec - len;
		tmp = ft_strnew(i);
		while (--i >= 0)
			tmp[i] = '0';
		res = ft_strjoin(tmp, o->out);
		free(tmp);
		free(o->out);
		o->out = res;
	}
}

void	digit_width_print(t_pf_env *o)
{
	int i;
	int len;

	i = -1;
	if ((int)ft_strlen(o->out) > o->flmd.prec)
		len = (int)ft_strlen(o->out);
	else
		len = o->flmd.prec;
	if ((o->flmd.plus + o->flmd.space + o->flmd.neg) >= 1)
		o->flmd.width--;
	if (o->flmd.prec >= 0)
	{
		while (o->flmd.width - ++i > len)
			o->ret += write(o->fd, " ", 1);
		i = -1;
		while ((int)ft_strlen(o->out) < len - ++i)
			o->ret += write(o->fd, "0", 1);
	}
	else
		while (o->flmd.width - ++i > len)
			o->ret += (o->flmd.zero == 1 ?
			write(o->fd, "0", 1) : write(o->fd, " ", 1));
}

void	prec_width_print(t_pf_env *o)
{
	int i;
	int len;

	i = -1;
	len = ft_strlen(o->out) + o->flmd.plus + o->flmd.space;
	if (o->flmd.prec >= 0)
	{
		while (o->flmd.width - ++i > len)
			if (o->flmd.zero)
				o->ret += write(o->fd, "0", 1);
			else
				o->ret += write(o->fd, " ", 1);
		i = -1;
		while ((int)ft_strlen(o->out) < len - ++i)
			o->ret += write(o->fd, "0", 1);
	}
	else
		while (o->flmd.width - ++i > len)
			if (o->flmd.zero == 1)
				o->ret += write(o->fd, "0", 1);
			else
				o->ret += write(o->fd, " ", 1);
}
