/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:26:56 by hna               #+#    #+#             */
/*   Updated: 2020/03/12 21:27:43 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

#include "libft.h"
#include <stdio.h>
#include <stdarg.h>

typedef	struct		s_option
{
	int		len;
	int		width;
	int		prec;
	int		minus;
	char	pad;
}					t_option;

int		is_numeric(int c);
int		is_flag(int c);
int		is_conv(int c);
void	ft_putnstr(char *str, int n, t_option *opt);
char 	*make_padstr(int size, char pad);
int		parse_flag(t_option *opt, va_list ap, char *str, int *i);
int		print_perc(t_option *opt);
int		print_int(t_option *opt, va_list ap);
int		print_uint(t_option *opt, va_list ap);
int		print_char(t_option *opt, va_list ap);
int		print_hex(t_option *opt, va_list ap, char mode);
int		print_str(t_option *opt, va_list ap);
int		print_paddr(t_option *opt, va_list ap);
char	*freejoin(char *s1, char *s2);
int		ft_printf(const char *str, ...);

#endif
