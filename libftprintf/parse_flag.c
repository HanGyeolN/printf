/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 22:29:39 by hna               #+#    #+#             */
/*   Updated: 2020/03/12 22:29:50 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	set_pad_ii(t_option *opt, char c, int *idx)
{
	opt->pad = c;
	*idx += 1;
}

void	set_minus_ii(t_option *opt, int n, int *idx)
{
	opt->minus = n;
	*idx += 1;
}

void	skip_numeric(char *str, int *i)
{
	while (is_numeric(str[*i]))
		*i += 1;
}

void	parse_precision(t_option *opt, va_list ap, char *str, int *i)
{
	*i += 1;
	opt->prec = 0;
	if (is_numeric(str[*i]))
	{
		opt->prec = ft_atoi(&str[*i]);
		skip_numeric((char *)str, i);
	}
	else if (str[*i] == '*')
	{
		opt->prec = va_arg(ap, int);
		*i += 1;
	}
}

int		parse_flag(t_option *opt, va_list ap, char *str, int *i)
{
	*i += 1;
	while (!is_conv(str[*i]))
	{
		if (str[*i] == '\0')
			return (-1);
		else if (str[*i] == '0')
			set_pad_ii(opt, '0', i);
		else if (str[*i] == '-')
			set_minus_ii(opt, 1, i);
		else if (str[*i] == '*')
		{
			opt->width = va_arg(ap, int);
			*i += 1;
		}
		else if (str[*i] == '.')
			parse_precision(opt, ap, str, i);
		else if (is_numeric(str[*i]))
		{
			opt->width = ft_atoi(&str[*i]);
			skip_numeric((char *)str, i);
		}
		else
			*i += 1;
	}
	return (0);
}
