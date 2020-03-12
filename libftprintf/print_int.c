/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 22:30:55 by hna               #+#    #+#             */
/*   Updated: 2020/03/12 22:31:03 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int  check_minus(t_option *opt, char *temp)
{
    if (opt->width < -1)
	{
		opt->width = -(opt->width);
		opt->minus = 1;
	}
	if (opt->prec < -1)
	{
		opt->prec = (temp[0] == '-') ? ft_strlen(temp) - 1 : ft_strlen(temp);
		opt->minus = 1;
	}
    if (opt->prec == 0)
		temp[0] = '\0';
    return (0);
}

static int	check_width_p(t_option *opt, char *s_pad, char *s_prec, char *temp)
{
	if (!(s_pad = make_padstr(opt->width, opt->pad)))
		return (-1);
	if (opt->minus == 1)
	{
		ft_strncpy(s_pad, s_prec, ft_strlen(s_prec));
		ft_memset(&s_pad[ft_strlen(s_prec)], ' ', opt->width - ft_strlen(s_prec));
	}
	else
	{
		if (temp[0] == '-')
			ft_strncpy(&s_pad[opt->width - opt->prec - 1], s_prec, ft_strlen(s_prec));
		else
			ft_strncpy(&s_pad[opt->width - opt->prec], s_prec, ft_strlen(s_prec));
		if (temp[0] == '-')
			ft_memset(s_pad, ' ', opt->width - ft_strlen(s_prec));
		else
			ft_memset(s_pad, ' ', opt->width - ft_strlen(s_prec));
	}
	ft_putnstr(s_pad, ft_strlen(s_pad), opt);
	free(s_pad);
	return (0);
}

static int	check_prec(t_option *opt, char *s_prec, char *s_pad, char *temp)
{
	char	*tmp_prec;

	if (!(s_prec = make_padstr(opt->prec, '0')))
		return (-1);
	if (temp[0] == '-')
	{
		ft_strncpy(&s_prec[opt->prec - ft_strlen(temp) + 1], &temp[1], ft_strlen(temp));
		tmp_prec = malloc(sizeof(char) * (ft_strlen(s_prec) + 2));
		tmp_prec[0] = '-';
		ft_strcpy(&tmp_prec[1], s_prec);
		tmp_prec[opt->prec + 1] = '\0';
		free(s_prec);
		s_prec = tmp_prec;
	}
	else
		ft_strncpy(&s_prec[opt->prec - ft_strlen(temp)], temp, ft_strlen(temp));
	if (opt->width > opt->prec)
	{
		if (check_width_p(opt, s_pad, s_prec, temp) == -1)
			return (-1);
	}
	else
		ft_putnstr(s_prec, ft_strlen(s_prec), opt);
	free(s_prec);
	return (0);
}

static int	check_width(t_option *opt, char *s_pad, char *temp)
{
	if (opt->prec != -1 && opt->prec <= ft_strlen(temp))
	{
		if (!(s_pad = make_padstr(opt->width, ' ')))
			return (-1);
	}
	else
	{
		if (!(s_pad = make_padstr(opt->width, opt->pad)))
			return (-1);
	}
	if (opt->minus == 1)
	{
		free(s_pad);
		if (!(s_pad = make_padstr(opt->width, ' ')))
			return (-1);
		ft_strncpy(s_pad, temp, ft_strlen(temp));
	}
	else
		ft_strcpy(&s_pad[opt->width - ft_strlen(temp)], temp);
	if (temp[0] == '-' && s_pad[0] == '0')
		ft_swap(&s_pad[opt->width - ft_strlen(temp)], &s_pad[0]);
	ft_putnstr(s_pad, ft_strlen(s_pad), opt);
	free(s_pad);
	return (0);
}

int		print_int(t_option *opt, va_list ap)
{
	char	*temp;
	char	*s_pad;
	char	*s_prec;

	s_pad = 0;
	s_prec = 0;
	if (!(temp = ft_itoa((int)va_arg(ap, int))))
        return (-1);
    check_minus(opt, temp);
	if ((opt->prec > ft_strlen(temp) && temp[0] != '-' ) ||
        (opt->prec > ft_strlen(temp) - 1 && temp[0] == '-'))
	{
		if (check_prec(opt, s_prec, s_pad, temp) == -1)
			return (-1);
	}
	else if (opt->width > ft_strlen(temp))
	{
		if (check_width(opt, s_pad, temp) == -1)
			return (-1);
	}
	else
		ft_putnstr(temp, ft_strlen(temp), opt);
	free(temp);
	return (0);
}
