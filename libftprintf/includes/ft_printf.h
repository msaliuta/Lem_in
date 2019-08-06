/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaliuta <msaliuta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 18:17:20 by msaliuta          #+#    #+#             */
/*   Updated: 2019/07/17 07:49:00 by msaliuta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"
# include <wchar.h>
# include <limits.h>
# include <stdarg.h>

# define CHECK_PCNT(i) (i == '%')
# define CHECK_COLOR(i) (i == '%')
# define FLAGS " 0123456789Lhjltz#+-*."
# define CONV_FLAGS " 0#+-"
# define INUM(i) (i >= '0' && i <= '9')
# define INUM1(i) (i >= '1' && i <= '9')
# define CHECK_BONUS(i) (i == 'r')
# define CHECK_INT(i) (i == 'd' || i == 'i')
# define CHECK_UINT(i) (i == 'u' || i == 'D' || i == 'U')
# define CHECK_CHR(i) (i == 'c' || i == 's')
# define CHECK_LCHR(i) (i == 'C' || i == 'S')
# define CHECK_PRC(i) (i == 'F' || i == 'A' || i == 'G'|| i == 'E')
# define CHECK_LPRC(i) (i == 'f' || i == 'a' || i == 'g'|| i == 'e')
# define CHECK_HEX(i) (i == 'b' || i == 'o' || i == 'x')
# define CHECK_LHEX(i) (i == 'B' || i == 'O' || i == 'X')
# define IN(i) (i == 'n')

typedef struct	s_pf_tag
{
	int			pos;
	int			tag;
}				t_pf_tag;

typedef struct	s_pf_flmd
{
	int			space;
	int			plus;
	int			neg;
	int			minus;
	int			hash;
	int			zero;
	int			prec;
	int			width;
}				t_pf_flmd;

# define NOMOD 0
# define J 1
# define Z 2
# define T 3
# define H 4
# define HH 5
# define L 6
# define LL 8
# define L1 9

typedef	struct	s_pf_env
{
	va_list		ap[2];
	char		*out;
	int			fd : 2;
	int			i : 15;
	t_pf_tag	tag;
	t_pf_flmd	flmd;
	int			mod : 6;
	int			ret;
}				t_pf_env;

/*
**ft_printf.c
*/

int				ft_printf(const char *restrict frmt, ...);
void			start_fpf(const char *restrict frmt, t_pf_env *o);
void			parse_flags(const char *restrict frmt, t_pf_env *o);
void			check_conv_flag(const char *restrict frmt, t_pf_env *o);
void			parce_modif(const char *restrict frmt, t_pf_env *o);

/*
**parse_mfw.c
*/

void			parse_mfw(const char *restrict frmt, t_pf_env *o);
void			parse_size_spec(const char *restrict frmt, t_pf_env *o);
void			check_width(t_pf_env *o);
void			check_prec(const char *restrict frmt, t_pf_env *o);
void			parse_prec(t_pf_env *o, char type);

/*
**int_funct.c
*/

void			init_long_argm(t_pf_env *o, long *tmp);
void			process_int(t_pf_env *o);
void			init_double_argm(t_pf_env *o, double *tmp);
void			process_unsint(t_pf_env *o, char type);

/*
**longd_funct.c
*/

void			init_long_double(t_pf_env *o, long double *tmp);
void			check_form(t_pf_env *o, long double d, char tnt);
void			process_dgt_sign(t_pf_env *o);
void			process_dgt_prec(t_pf_env *o);

/*
**process_functs.c
*/

void			process_base(t_pf_env *o, char type);
void			process_return(t_pf_env *o);
void			process_ptraddr(t_pf_env *o, char type);
void			process_percent(t_pf_env *o);
void			process_nonprintable(t_pf_env *o);

/*
**print_functs.c
*/

void			digit_sign_print(t_pf_env *o);
void			digit_print(t_pf_env *o);
void			base_pre_print(t_pf_env *o, char type, long val);
void			bpp_check(t_pf_env *o, char type, int n);
void			base_print(t_pf_env *o, char type, long val);

/*
**print_wids_functs.c
*/

void			base_width_print(t_pf_env *o, char type);
void			bpw_check(t_pf_env *o, char type);
void			check_prec_base(t_pf_env *o, char type);
void			digit_width_print(t_pf_env *o);
void			prec_width_print(t_pf_env *o);

/*
**char_functs.c
*/

void			char_for_ptint(t_pf_env *o, int n);
void			process_char(t_pf_env *o, char type);
void			init_char_arg(t_pf_env *o, int *tmp);
void			char_print(t_pf_env *o, char c);

/*
**str_functs.c
*/

void			init_str_arg(t_pf_env *o, char **tmp);
void			str_print(t_pf_env *o);
void			str_for_print(t_pf_env *o, int n);
char			*ft_str_prec(char *s1, int dot, int end, int hash);
void			prrint_wstr_1(t_pf_env *o, char c);

/*
**ftoa_functs.c
*/

void			ftoa_a(t_pf_env *o, double d, char type);
void			ftoa_e(t_pf_env *o, long double d, char type, int prec);
void			ftoa_fg(t_pf_env *o, long double d, int end, long	num);
void			ftoa_eg(t_pf_env *o, long double d, char type, int prec);
void			ftoa_f(t_pf_env *o, long double d, long num);

/*
**wchar_functs.c
*/

void			print_wchar(t_pf_env *o, wchar_t wc);
void			wchar_init(t_pf_env *o, wchar_t *tmp);
void			process_wchar(t_pf_env *o, char type);
void			prrint_wchar_1(t_pf_env *o, char c);
void			check_wchar(t_pf_env *o, wchar_t c);

/*
**wstr_functs.c
*/

void			wstr_min_print(t_pf_env *o, wchar_t *wc, int len);
int				get_wstr_len(wchar_t *wc);
void			print_wstr(t_pf_env *o, wchar_t *wc);
void			wstr_init(t_pf_env *o, wchar_t **tmp);
void			check_wstr(t_pf_env *o, wchar_t c);

/*
**bonus_funct.c
*/

void			print_pf_thirtd_dec(t_pf_env *o, char c);
void			print_second_dec(t_pf_env *o, char c);
void			print_first_dec(t_pf_env *o, char c);

/*
**prec_print_functs.c
*/

void			prec_print(t_pf_env *o, double d, char type, int k);
void			print_prec_a(t_pf_env *o, double d, char type);
void			prec_print_hp(long double d, t_pf_env *o);

/*
**get_functs.c
*/

long			get_prec_num_f(long double d, int prec);
void			get_a_expo(double d, char type, char **oxpo);
long			get_prec_num_e(long double d, int prec);
void			get_exponent(long double d, char type, char **oxpo, int ex);

/*
**print_wdthpdr.c
*/
void			ptraddr_prec(t_pf_env *o);
void			print_ptraddr_width(t_pf_env *o);
void			print_invalid_width(t_pf_env *o);
void			print_ptraddr(t_pf_env *o, char type);
void			print_invalid_spec(t_pf_env *o, char c);

/*
**.c
*/

void			hex_prec(t_pf_env *o, double d, char **frac, char type);
void			delete_zero(char *tmp);
void			nan_inf(t_pf_env *o, char type, double var);
char			*ft_ftoa(long double d);

#endif
