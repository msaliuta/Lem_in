/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longd_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:11 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:00 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_long_double(t_pf_env *o, long double *tmp)
{
	if (o->tag.tag)
	{
		va_copy(o->ap[0], o->ap[1]);
		while (--o->tag.pos >= 0)
			*tmp = va_arg(o->ap[0], long double);
		return ;
	}
	*tmp = va_arg(o->ap[0], long double);
}

void	check_form(t_pf_env *o, long double d, char tnt)
{
	char	*nb;
	int		neg;

	if (d < 0)
		neg = -1;
	else
		neg = 1;
	d *= neg;
	if ((d + 0.5 > 1000000 || d < 0.0001) && o->flmd.prec < 0 &&
		d != 0)
		return (ftoa_eg(o, d * neg, tnt - 2, 5));
	else if (o->flmd.prec < 0)
		return (ftoa_fg(o, d * neg, 6, 0));
	nb = ft_ltoa((long)d);
	if (((int)ft_strlen(nb) > o->flmd.prec && o->flmd.prec != 0) ||
		(o->flmd.prec == 0 && d >= 10))
	{
		free(nb);
		return (ftoa_eg(o, d * neg, tnt - 2, o->flmd.prec - 1));
	}
	free(nb);
	ftoa_fg(o, d * neg, o->flmd.prec, 0);
}

void	process_dgt_sign(t_pf_env *o)
{
	char *tmp;

	if (o->out[0] == '-')
	{
		tmp = ft_strdup(o->out + 1);
		free(o->out);
		o->out = tmp;
		o->flmd.space = 0;
		o->flmd.plus = 0;
		o->flmd.neg = 1;
	}
}

void	process_dgt_prec(t_pf_env *o)
{
	char	*tmp;
	char	*res;
	int		len;
	int		i;

	process_dgt_sign(o);
	len = (int)ft_strlen(o->out);
	if (o->flmd.prec == 0 && o->out[0] == '0')
		o->out[0] = '\0';
	else if (o->flmd.prec > len)
	{
		i = o->flmd.prec - len;
		tmp = ft_strnew(i);
		while (i-- > 0)
			tmp[i] = '0';
		res = ft_strjoin(tmp, o->out);
		free(tmp);
		free(o->out);
		o->out = res;
	}
}
