/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_wdthpdr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:19 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:00 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ptraddr_prec(t_pf_env *o)
{
	char	*tmp;
	char	*res;
	int		len;
	int		i;

	i = -1;
	len = (int)ft_strlen(o->out);
	if (o->flmd.prec > len)
	{
		tmp = ft_strnew(o->flmd.prec - len);
		while (++i < o->flmd.prec - len)
			tmp[i] = '0';
		res = ft_strjoin(tmp, o->out);
		free(o->out);
		free(tmp);
		o->out = res;
	}
	tmp = ft_strjoin("0x", o->out);
	free(o->out);
	o->out = tmp;
}

void	print_ptraddr_width(t_pf_env *o)
{
	int len;

	len = ft_strlen(o->out);
	while (o->flmd.width-- > len)
		o->ret += write(o->fd, " ", 1);
}

void	print_ptraddr(t_pf_env *o, char type)
{
	if (o->flmd.zero && o->flmd.prec == -1)
		o->flmd.prec = o->flmd.width - 2;
	ptraddr_prec(o);
	if (type == 'p')
		ft_strlower(o->out);
	if (o->flmd.minus)
	{
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
		print_ptraddr_width(o);
	}
	else
	{
		print_ptraddr_width(o);
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
	}
	++o->i;
	free(o->out);
}

void	print_invalid_width(t_pf_env *o)
{
	while (o->flmd.width-- > 1)
	{
		if (o->flmd.zero == 1)
			o->ret += write(o->fd, "0", 1);
		else
			o->ret += write(o->fd, " ", 1);
	}
}

void	print_invalid_spec(t_pf_env *o, char c)
{
	if (o->flmd.minus)
	{
		o->ret += write(o->fd, &c, 1);
		print_invalid_width(o);
	}
	else
	{
		print_invalid_width(o);
		o->ret += write(o->fd, &c, 1);
	}
	++o->i;
}
