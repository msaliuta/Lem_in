/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_functs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:20 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:00 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	str_for_print(t_pf_env *o, int n)
{
	if (n == 1)
	{
		n = ft_strlen(o->out);
		while (o->flmd.width-- > n)
			if (o->flmd.zero == 1)
				o->ret += write(o->fd, "0", 1);
			else
				o->ret += write(o->fd, " ", 1);
	}
	else
	{
		if (o->flmd.prec < 0)
			n = 6;
		else
			n = o->flmd.prec;
		while (o->flmd.width-- > n)
			if (o->flmd.zero == 1)
				o->ret += write(o->fd, "0", 1);
			else
				o->ret += write(o->fd, " ", 1);
		o->ret += write(o->fd, "(null)", n);
		++o->i;
	}
}

void	str_print(t_pf_env *o)
{
	char	*tmp;

	if (o->flmd.prec >= 0 && o->flmd.prec < (int)ft_strlen(o->out))
	{
		tmp = ft_strsub(o->out, 0, (o->flmd.prec));
		free(o->out);
		o->out = tmp;
	}
	if (o->flmd.minus)
	{
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
		str_for_print(o, 1);
	}
	else
	{
		str_for_print(o, 1);
		o->ret += write(o->fd, o->out, ft_strlen(o->out));
	}
	++o->i;
	free(o->out);
}

void	init_str_arg(t_pf_env *o, char **tmp)
{
	if (o->tag.tag)
	{
		va_copy(o->ap[0], o->ap[1]);
		while (o->tag.pos >= 0)
		{
			*tmp = va_arg(o->ap[0], char *);
			o->tag.pos--;
		}
		return ;
	}
	*tmp = va_arg(o->ap[0], char *);
}

char	*ft_str_prec(char *s1, int dot, int end, int hash)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_strnew(ft_strlen(s1) + 1);
	while (s1[i] != '\0')
	{
		tmp[j++] = s1[i];
		if ((i == dot - 1 && end > 0) || hash == 1)
		{
			tmp[j++] = '.';
			hash = 0;
		}
		if (i >= end)
		{
			tmp[j] = '\0';
			break ;
		}
		i++;
	}
	return (tmp);
}

void	prrint_wstr_1(t_pf_env *o, char c)
{
	o->ret += write(o->fd, &c, 1);
}
