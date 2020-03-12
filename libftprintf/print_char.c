/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 22:30:24 by hna               #+#    #+#             */
/*   Updated: 2020/03/12 22:30:35 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	check_zero(t_option *opt, char *str, char *temp)
{
	if (temp[0] == 0)
		ft_putnstr(str, ft_strlen(str) + 1, opt);
	else
		ft_putnstr(str, ft_strlen(str), opt);
}

static int	check_prec(t_option *opt, char *s_prec, char *s_pad, char *temp)
{
	if (!(s_prec = make_padstr(opt->prec, '0')))
		return (-1);
	ft_strncpy(&s_prec[opt->prec - 1], temp, 1);
	if (opt->width > opt->prec)
	{
		if (!(s_pad = make_padstr(opt->width, opt->pad)))
			return (-1);
		if (opt->minus == 1)
			ft_strncpy(s_pad, s_prec, ft_strlen(s_prec));
		else
			ft_strncpy(&s_pad[opt->width - opt->prec], s_prec, ft_strlen(s_prec));
		check_zero(opt, s_pad, temp);
		free(s_pad);
	}
	else
		check_zero(opt, s_prec, temp);
	free(s_prec);
	return (0);
}

static int	check_width(t_option *opt, char *s_pad, char *temp)
{
	if (!(s_pad = make_padstr(opt->width, opt->pad)))
		return (-1);
	if (opt->minus == 1)
		ft_strncpy(s_pad, temp, 1);
	else
		ft_strcpy(&s_pad[opt->width - 1], temp);
	ft_putnstr(s_pad, opt->width, opt);
	free(s_pad);
	return (0);
}

int		print_char(t_option *opt, va_list ap)
{
	char			*temp;
	char			*s_pad;
	char			*s_prec;

	s_pad = 0;
	s_prec = 0;
	if (!(temp = malloc(sizeof(char) * 2)))
		return (-1);
	temp[0] = (char)va_arg(ap, int);
	temp[1] = '\0';
	if (opt->prec > 1)
	{
		if (check_prec(opt, s_prec, s_pad, temp) == -1)
			return (-1);
	}
	else if (opt->width > 1)
	{
		if (check_width(opt, s_pad, temp) == -1)
			return (-1);
	}
	else
		ft_putnstr(temp, 1, opt);
	free(temp);
	return (0);
}
