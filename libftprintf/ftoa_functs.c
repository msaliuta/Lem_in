/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa_functs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 10:43:23 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:00 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ftoa_a(t_pf_env *o, double d, char type)
{
	char	*frac;
	char	*ep;
	char	*tmp;

	d == 0 ? frac = ft_strdup("0") : hex_prec(o, d, &frac, type);
	if (d != 0)
		delete_zero(frac);
	get_a_expo(d, type, &ep);
	if (frac[0] == '\0')
		o->out = (d == 0 ? ft_strjoin("0", ep) : ft_strjoin("1", ep));
	else
	{
		tmp = (d == 0 ? ft_strdup(frac) : ft_strjoin("1.", frac));
		o->out = ft_strjoin(tmp, ep);
		free(tmp);
	}
	free(frac);
	free(ep);
	if (d < 0)
	{
		o->flmd.plus = 0;
		o->flmd.space = 0;
		--o->flmd.width;
	}
}

void	ftoa_e(t_pf_env *o, long double d, char type, int prec)
{
	char	*tmp;
	char	*nb;
	char	*expo;
	long	num;

	prec = (o->flmd.prec >= 0 ? o->flmd.prec : 6);
	if (d != 0)
	{
		num = get_prec_num_e(d, prec);
		nb = ft_ftoa(num);
		get_exponent(d, type, &expo, 0);
	}
	else
	{
		expo = ft_strjoin(&type, "+00");
		num = 0;
		nb = ft_strdup("0000000");
	}
	tmp = (d < 0 ? ft_str_prec(nb, 2, prec + 1, o->flmd.hash)
	: ft_str_prec(nb, 1, prec, o->flmd.hash));
	o->out = ft_strjoin(tmp, expo);
	free(nb);
	free(tmp);
	free(expo);
}

void	ftoa_fg(t_pf_env *o, long double d, int end, long num)
{
	char	*tmp;
	char	*nb;
	int		prec;

	tmp = ft_ltoa((long)d);
	end -= ft_strlen(tmp) - 1;
	if (d == 0)
	{
		--o->flmd.prec;
		--end;
	}
	prec = ft_strlen(tmp);
	num = get_prec_num_f(d, end);
	if (num == 0)
		nb = ft_strdup("0000000");
	else
		nb = ft_ftoa(num);
	if ((end <= prec || d == (long)d) && o->flmd.hash == 0)
		o->out = ft_strdup(tmp);
	else
		o->out = ft_str_prec(nb, prec, end, 0);
	if (!o->flmd.hash && d - (long)d != 0)
		delete_zero(o->out);
	free(tmp);
	free(nb);
}

void	ftoa_eg(t_pf_env *o, long double d, char type, int prec)
{
	char	*tmp;
	char	*nb;
	char	*expo;
	long	num;

	if (prec == 1)
		prec = 0;
	num = get_prec_num_e(d, prec);
	nb = ft_ftoa(num);
	get_exponent(d, type, &expo, 0);
	if (d < 0)
		tmp = ft_str_prec(nb, 2, prec + 1, o->flmd.hash);
	else
		tmp = ft_str_prec(nb, 1, prec, o->flmd.hash);
	if (!o->flmd.hash)
		delete_zero(tmp);
	o->out = ft_strjoin(tmp, expo);
	free(nb);
	free(tmp);
	free(expo);
}

void	ftoa_f(t_pf_env *o, long double d, long num)
{
	char	*tmp;
	char	*nb;
	int		prec;

	tmp = ft_ltoa((long)d);
	if (d == 0)
		--o->flmd.prec;
	prec = ft_strlen(tmp);
	if (o->flmd.prec >= 0)
		num = get_prec_num_f(d, o->flmd.prec);
	else
		num = get_prec_num_f(d, 6);
	if (num == 0)
		nb = ft_strdup("0000000");
	else
		nb = ft_ftoa(num);
	if (o->flmd.prec == 0 && o->flmd.hash)
		o->out = ft_strjoin(tmp, ".");
	else if (o->flmd.prec == 0 && !o->flmd.hash)
		o->out = ft_strdup(tmp);
	else
		o->out = ft_str_prec(nb, prec, o->flmd.prec >= 0 ?
		prec + o->flmd.prec : prec + 6, o->flmd.hash);
	free(nb);
	free(tmp);
}
