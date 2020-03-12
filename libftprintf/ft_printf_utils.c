/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 21:22:49 by hna               #+#    #+#             */
/*   Updated: 2020/03/12 22:29:17 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		is_numeric(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int		is_flag(int c)
{
	if (c == '.' || c == '-' || c == '*' || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int		is_conv(int c)
{
	if (ft_strchr("cspdiuxX%", c))
		return (1);
	return (0);
}

void	ft_putnstr(char *str, int n, t_option *opt)
{
	int		i;

	i = 0;
	while (i < n)
	{
		ft_putchar(str[i]);
		(opt->len)++;
		i++;
	}
}

char 	*make_padstr(int size, char pad)
{
	char	*padstr;

	if (!(padstr = malloc(sizeof(char) * (size + 1))))
		return (0);
	ft_memset(padstr, pad, size);
	padstr[size] = '\0';
	return (padstr);
}
