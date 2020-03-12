/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_perc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 22:31:20 by hna               #+#    #+#             */
/*   Updated: 2020/03/12 22:31:25 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int  check_width_with_prec(t_option *opt, char *s_prec, char *s_pad)
{
    if (!(s_pad = make_padstr(opt->width, opt->pad)))
    {
        free(s_prec);
        return (-1);
    }
    if (opt->minus == 1)
        ft_strncpy(s_pad, s_prec, ft_strlen(s_prec));
    else
        ft_strncpy(&s_pad[opt->width - opt->prec], s_prec, ft_strlen(s_prec));
    ft_putnstr(s_pad, ft_strlen(s_pad), opt);
    free(s_pad);
    free(s_prec);
    return (0);
}

static int  check_prec(t_option *opt, char *s_prec, char *s_pad, char *temp)
{
    if (!(s_prec = make_padstr(opt->prec, '0')))
		return (-1);
    ft_strncpy(&s_prec[opt->prec - 1], temp, 1);
    if (opt->width > opt->prec)
    {
        if (check_width_with_prec(opt, s_prec, s_pad) == -1)
            return (-1);
    }
    else
    {
        ft_putnstr(s_prec, ft_strlen(s_prec), opt);
        free(s_prec);
    }
    return (0);
}

static int  check_width(t_option *opt, char *s_pad, char *temp)
{
    if (opt->minus == 1)
        opt->pad = ' ';
    if (!(s_pad = make_padstr(opt->width, opt->pad)))
        return (-1);
    if (opt->minus == 1)
        ft_strncpy(s_pad, temp, 1);
    else
        ft_strcpy(&s_pad[opt->width - 1], temp);
    ft_putnstr(s_pad, ft_strlen(s_pad), opt);
    free(s_pad);
    return (0);
}

int		print_perc(t_option *opt)
{
	char			*temp;
	char			*s_pad;
	char			*s_prec;

	if (!(temp = malloc(sizeof(char) * 2)))
        return (-1);
	temp[0] = '%';
	temp[1] = '\0';
    s_pad = 0;
    s_prec = 0;
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
