/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 22:31:32 by hna               #+#    #+#             */
/*   Updated: 2020/03/12 22:31:37 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	init_temp(t_option *opt, char **temp, va_list ap)
{
	*temp = (char *)va_arg(ap, char *);
	if (*temp == 0)
	{
		if (!(*temp = malloc(sizeof(char) * 7)))
			return (0);
		ft_strcpy(*temp, "(null)");
	}
	if (opt->width < -1)
	{
		opt->width = -(opt->width);
		opt->minus = 1;
	}
	if (opt->prec < -1)
	{
		opt->prec = ft_strlen(*temp);
		opt->minus = 1;
	}
	return (1);
}

static void	check_minus(t_option *opt, char **s_pad, char **s_prec)
{
	int		len;

	len = ft_strlen(*s_prec);
	if (opt->minus == 1)
	{
		ft_strncpy(*s_pad, *s_prec, len);
		ft_memset(&((*s_pad)[len]), ' ', opt->width - len);
	}
	else
	{
		ft_strncpy(&((*s_pad)[opt->width - opt->prec]), *s_prec, len);
		ft_memset(*s_pad, ' ', opt->width - len);
	}
}

static int	check_prec(t_option *opt, char *s_prec, char *s_pad, char *temp)
{
	if (!(s_prec = make_padstr(opt->prec, ' ')))
		return (-1);
	ft_strncpy(s_prec, temp, opt->prec);
	if (opt->width > opt->prec)
	{
		if (!(s_pad = make_padstr(opt->width, opt->pad)))
			return (-1);
		check_minus(opt, &s_pad, &s_prec);
		ft_putnstr(s_pad, ft_strlen(s_pad), opt);
		free(s_pad);
	}
	else
		ft_putnstr(s_prec, ft_strlen(s_prec), opt);
	free(s_prec);
	return (0);
}

static int	check_width(t_option *opt, char *s_pad, char *s_prec, char *temp)
{
	if (opt->minus == 1)
		opt->pad = ' ';
	if (!(s_pad = make_padstr(opt->width, opt->pad)))
		return (-1);
	if (opt->minus == 1)
		ft_strncpy(s_pad, temp, ft_strlen(temp));
	else
		ft_strcpy(&s_pad[opt->width - ft_strlen(temp)], temp);
	if (opt->prec < ft_strlen(temp) && opt->prec > 0)
	{
		if (!(s_prec = make_padstr(opt->prec, ' ')))
			return (-1);
		ft_strncpy(&s_prec[opt->prec - ft_strlen(temp)], temp, opt->prec);
		check_minus(opt, &s_pad, &s_prec);
		ft_putnstr(s_pad, ft_strlen(s_pad), opt);
		free(s_prec);
	}
	else
		ft_putnstr(s_pad, ft_strlen(s_pad), opt);
	free(s_pad);
	return (0);
}

int		print_str(t_option *opt, va_list ap)
{
	char	*temp;
	char	*s_pad;
	char	*s_prec;

	s_pad = 0;
	s_prec = 0;
	if (!(init_temp(opt, &temp, ap)))
		return (-1);
	if (opt->prec < ft_strlen(temp) && opt->prec != -1)
	{
		if (check_prec(opt, s_prec, s_pad, temp) == -1)
			return (-1);
	}
	else if (opt->width > ft_strlen(temp))
	{
		if (check_width(opt, s_pad, s_prec, temp) == -1)
			return (-1);
	}
	else
		ft_putnstr(temp, ft_strlen(temp), opt);
	return (0);
}
