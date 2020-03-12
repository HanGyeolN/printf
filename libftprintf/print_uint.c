#include "libft.h"

int		print_uint(t_option *opt, va_list ap)
{
	unsigned int	u_temp;
	char			*temp;
	char			*s_pad;
	char			*s_prec;

	u_temp = (unsigned int)va_arg(ap, int);
	temp = ft_itoa_u(u_temp);
	if (opt->prec == 0)
		temp[0] = '\0';
	if (opt->prec > ft_strlen(temp))
	{
		if (!(s_prec = make_padstr(opt->prec, '0')))
			return (-1);
		ft_strncpy(&s_prec[opt->prec - ft_strlen(temp)], temp, ft_strlen(temp));
		if (opt->width > opt->prec)
		{
			opt->pad = ' ';
			if (!(s_pad = make_padstr(opt->width, opt->pad)))
				return (-1);
			if (opt->minus == 1)
				ft_strncpy(s_pad, s_prec, ft_strlen(s_prec));
			else
				ft_strncpy(&s_pad[opt->width - opt->prec], s_prec, ft_strlen(s_prec));
			ft_putnstr(s_pad, ft_strlen(s_pad), opt);
			free(s_pad);
			free(s_prec);
		}
		else
		{
			ft_putnstr(s_prec, ft_strlen(s_prec), opt);
			free(s_prec);
		}
	}
	else if (opt->width > ft_strlen(temp))
	{
		if (opt->prec != -1 && opt->prec < ft_strlen(temp))
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
			ft_strncpy(s_pad, temp, ft_strlen(temp));
		else
			ft_strcpy(&s_pad[opt->width - ft_strlen(temp)], temp);
		ft_putnstr(s_pad, ft_strlen(s_pad), opt);
		free(s_pad);
	}
	else
	{
		ft_putnstr(temp, ft_strlen(temp), opt);
	}
	free(temp);
	return (0);
}