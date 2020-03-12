/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_paddr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 22:31:09 by hna               #+#    #+#             */
/*   Updated: 2020/03/12 22:31:15 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	check_width_with_prec(t_option *opt, char *s_pad, char *s_prec)
{
	int		prec_len;

	prec_len = ft_strlen(s_prec);
	if (!(s_pad = make_padstr(opt->width, opt->pad)))
		return (-1);
	if (opt->minus == 1)
	{
		ft_strncpy(s_pad, s_prec, prec_len);
		ft_memset(&s_pad[prec_len], ' ', opt->width - prec_len);
	}
	else
	{
		ft_strncpy(&s_pad[opt->width - opt->prec], s_prec, prec_len);
		ft_memset(s_pad, ' ', opt->width - prec_len);
	}
	ft_putnstr(s_pad, ft_strlen(s_pad), opt);
	free(s_pad);
	return (0);
}

static int	check_prec(t_option *opt, char *s_prec, char *s_pad, char *temp)
{
	if (!(s_prec = make_padstr(opt->prec, '0')))
		return (-1);
	ft_strncpy(&s_prec[opt->prec - ft_strlen(temp)], temp, ft_strlen(temp));
	if (!(s_prec = freejoin("0x", s_prec)))
		return (-1);
	if (opt->width > opt->prec)
	{
		if (check_width_with_prec(opt, s_pad, s_prec) == -1)
			return (-1);
	}
	else
		ft_putnstr(s_prec, ft_strlen(s_prec), opt);
	free(s_prec);
	return (0);
}

static int	check_width(t_option *opt, char *s_pad, char *temp)
{
	if (!(s_pad = make_padstr(opt->width, opt->pad)))
		return (0);
	if (opt->minus == 1)
		ft_strncpy(s_pad, temp, ft_strlen(temp));
	else
		ft_strcpy(&s_pad[opt->width - ft_strlen(temp)], temp);
	ft_putnstr(s_pad, ft_strlen(s_pad), opt);
	free(s_pad);
	return (1);
}

static int	init_temp(t_option *opt, char **temp, va_list ap, char **p)
{
	*p = 0;
	if (!(*temp = ft_itoa_base_ll(va_arg(ap, long long), "0123456789abcdef")))
		return (-1);
	if (opt->prec == 0)
		(*temp)[0] = '\0';
	return (0);
}

int			print_paddr(t_option *opt, va_list ap)
{
	char		*temp;
	char		*s_pad;
	char		*s_prec;

	s_pad = 0;
	if (init_temp(opt, &temp, ap, &s_prec) == -1)
		return (-1);
	if (opt->prec > ft_strlen(temp))
	{
		if (check_prec(opt, s_prec, s_pad, temp) == -1)
			return (-1);
	}
	else if (opt->width > ft_strlen(temp) + 2)
	{
		if (!(temp = freejoin("0x", temp)) || !check_width(opt, s_pad, temp))
			return (-1);
	}
	else
	{
		if (!(temp = freejoin("0x", temp)))
			return (-1);
		ft_putnstr(temp, ft_strlen(temp), opt);
	}
	free(temp);
	return (0);
}
