/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/03 04:25:17 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/08 17:17:36 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_first_dec(t_pf_env *o, char c)
{
	if (c == 0)
		write(o->fd, "[NUL]", 5);
	else if (c == 1)
		write(o->fd, "[SOH]", 5);
	else if (c == 2)
		write(o->fd, "[STX]", 5);
	else if (c == 3)
		write(o->fd, "[ETX]", 5);
	else if (c == 4)
		write(o->fd, "[EOT]", 5);
	else if (c == 5)
		write(o->fd, "[ENQ]", 5);
	else if (c == 6)
		write(o->fd, "[ACK]", 5);
	else if (c == 7)
		write(o->fd, "[BEL]", 5);
	else if (c == 8)
		write(o->fd, "[BS]", 4);
	else if (c == 9)
		write(o->fd, "[TAB]", 5);
	else if (c == 10)
		write(o->fd, "[LF]", 4);
}

void	print_second_dec(t_pf_env *o, char c)
{
	if (c == 11)
		write(o->fd, "[VT]", 5);
	else if (c == 12)
		write(o->fd, "[FF]", 4);
	else if (c == 13)
		write(o->fd, "[CR]", 4);
	else if (c == 14)
		write(o->fd, "[SO]", 4);
	else if (c == 15)
		write(o->fd, "[SI]", 4);
	else if (c == 16)
		write(o->fd, "[DLE]", 5);
	else if (c == 17)
		write(o->fd, "[DC1]", 5);
	else if (c == 18)
		write(o->fd, "[DC2]", 5);
	else if (c == 19)
		write(o->fd, "[DC3]", 5);
	else if (c == 20)
		write(o->fd, "[DC4]", 5);
}

void	print_pf_thirtd_dec(t_pf_env *o, char c)
{
	if (c == 21)
		write(o->fd, "[NAK]", 5);
	else if (c == 22)
		write(o->fd, "[SYN]", 5);
	else if (c == 23)
		write(o->fd, "[ETB]", 5);
	else if (c == 24)
		write(o->fd, "[CAN]", 5);
	else if (c == 25)
		write(o->fd, "[EM]", 4);
	else if (c == 26)
		write(o->fd, "[SUB]", 5);
	else if (c == 27)
		write(o->fd, "[ESC]", 5);
	else if (c == 28)
		write(o->fd, "[FS]", 4);
	else if (c == 29)
		write(o->fd, "[GS]", 4);
	else if (c == 30)
		write(o->fd, "[RS]", 4);
	else if (c == 31)
		write(o->fd, "[US]", 4);
}
