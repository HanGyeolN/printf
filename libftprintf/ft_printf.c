/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 22:30:06 by hna               #+#    #+#             */
/*   Updated: 2020/03/12 22:30:08 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		next_is_percent(const char *str, int *idx, t_option *opt)
{
	if (str[*idx + 1] == '%')
	{
		ft_putnstr("%", 1, opt);
		*idx += 2;
		return (1);
	}
	return (0);
}

void	init_option(t_option *opt)
{
	opt->width = -1;
	opt->prec = -1;
	opt->minus = -1;
	opt->pad = ' ';
}

int		convert_conv(char conv, t_option *opt, va_list ap)
{
	if (conv == 'd' || conv == 'i')
		print_int(opt, ap);
	else if (conv == 'u')
		print_uint(opt, ap);
	else if (conv == 'c')
		print_char(opt, ap);
	else if (conv == 'x' || conv == 'X')
		print_hex(opt, ap, conv);
	else if (conv == 's')
		print_str(opt, ap);
	else if (conv == 'p')
		print_paddr(opt, ap);
	else if (conv == '%')
		print_perc(opt);
	return (0);
}

int		convert_str(char *str, va_list ap)
{
	int			i;
	t_option	opt;

	i = 0;
	opt.len = 0;
	init_option(&opt);
	if (str == 0)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			init_option(&opt);
			if (next_is_percent(str, &i, &opt))
				continue ;
			if (parse_flag(&opt, ap, (char *)str, &i) == -1)
				return (-1);
			if (convert_conv(str[i], &opt, ap) == -1)
				return (-1);
		}
		else
			ft_putnstr((char *)&str[i], 1, &opt);
		i++;
	}
	return (opt.len);
}

int		ft_printf(const char *str, ...)
{
	va_list		ap;
	int			ret;
	
	va_start(ap, str);
	if ((ret = convert_str((char *)str, ap)) == -1)
		return (-1);
	va_end(ap);
	return (ret);
}
