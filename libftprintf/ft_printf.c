#include "libft.h"

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

int		find_idx(char *str, int c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
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

char 	*make_padstr(int size, char pad)
{
	char	*padstr;

	if (!(padstr = malloc(sizeof(char) * (size + 1))))
		return (0);
	ft_memset(padstr, pad, size);
	padstr[size] = '\0';
	return (padstr);
}

void	skip_numeric(char *str, int *i)
{
	while (is_numeric(str[*i]))
		*i += 1;
}

void	init_option(t_option *opt)
{
	opt->width = -1;
	opt->prec = -1;
	opt->minus = -1;
	opt->pad = ' ';
}

int		print_char(t_option *opt, va_list ap)
{
	unsigned char	c_temp;
	char			*temp;
	char			*s_pad;
	char			*s_prec;

	c_temp = (char)va_arg(ap, int);
	temp = malloc(sizeof(char) * 2);
	temp[0] = c_temp;
	temp[1] = '\0';
	if (opt->prec > 1)
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
			if (c_temp == 0)
				ft_putnstr(s_pad, ft_strlen(s_pad) + 1, opt);
			else
				ft_putnstr(s_pad, ft_strlen(s_pad), opt);
			free(s_pad);
			free(s_prec);
		}
		else
		{
			if (c_temp == 0)
				ft_putnstr(s_prec, ft_strlen(s_prec) + 1, opt);
			else
				ft_putnstr(s_prec, ft_strlen(s_prec), opt);
			free(s_prec);
		}
	}
	else if (opt->width > 1)
	{
		if (!(s_pad = make_padstr(opt->width, opt->pad)))
			return (-1);
		if (opt->minus == 1)
			ft_strncpy(s_pad, temp, 1);
		else
			ft_strcpy(&s_pad[opt->width - 1], temp);
		ft_putnstr(s_pad, opt->width, opt);
		free(s_pad);
	}
	else
	{
		ft_putnstr(temp, 1, opt);
	}
	free(temp);
	return (0);
}

int		print_hex(t_option *opt, va_list ap, char mode)
{
	int		n_temp;
	int		u_temp;
	char	*temp;
	char	*s_pad;
	char	*s_prec;

	n_temp = (int)va_arg(ap, int);
	if (n_temp < 0)
		u_temp = n_temp;
	if (mode == 'x')
		temp = ft_itoa_base(n_temp, "0123456789abcdef");
	else
		temp = ft_itoa_base(n_temp, "0123456789ABCDEF");
	if (opt->prec == 0)
		temp[0] = '\0';
	if (opt->prec > ft_strlen(temp))
	{
		if (!(s_prec = make_padstr(opt->prec, '0')))
			return (-1);
		ft_strncpy(&s_prec[opt->prec - ft_strlen(temp)], temp, ft_strlen(temp));
		if (opt->width > opt->prec)
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
				ft_strncpy(&s_pad[opt->width - opt->prec], s_prec, ft_strlen(s_prec));
				ft_memset(s_pad, ' ', opt->width - ft_strlen(s_prec));
			}
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
		if (opt->prec < ft_strlen(temp) && opt->prec != -1)
			opt->pad = ' ';
		if (!(s_pad = make_padstr(opt->width, opt->pad)))
			return (-1);
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

int		print_str(t_option *opt, va_list ap)
{
	char	*temp;
	char	*s_pad;
	char	*s_prec;

	temp = (char *)va_arg(ap, char *);
	if (temp == 0)
	{
		temp = malloc(sizeof(char) * 7);
		ft_strcpy(temp, "(null)");
	}
	if (opt->width < -1)
	{
		opt->width = -(opt->width);
		opt->minus = 1;
	}
	if (opt->prec < -1)
	{
		opt->prec = ft_strlen(temp);
		opt->minus = 1;
	}
	if (opt->prec < ft_strlen(temp) && opt->prec != -1)
	{
		if (!(s_prec = make_padstr(opt->prec, ' ')))
			return (-1);
		ft_strncpy(s_prec, temp, opt->prec);
		if (opt->width > opt->prec)
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
				ft_strncpy(&s_pad[opt->width - opt->prec], s_prec, ft_strlen(s_prec));
				ft_memset(s_pad, ' ', opt->width - ft_strlen(s_prec));
			}
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
		if (!(s_pad = make_padstr(opt->width, opt->pad)))
			return (-1);
		if (opt->minus == 1)
		{
			free(s_pad);
			if (!(s_pad = make_padstr(opt->width, ' ')))
				return (-1);
			ft_strncpy(s_pad, temp, ft_strlen(temp));
		}
		else
			ft_strcpy(&s_pad[opt->width - ft_strlen(temp)], temp);
		if (opt->width > opt->prec && opt->prec > 0 && opt->prec < ft_strlen(temp))
		{
			if (!(s_prec = make_padstr(opt->prec, ' ')))
				return (-1);
			ft_strncpy(&s_prec[opt->prec - ft_strlen(temp)], temp, opt->prec);
			if (opt->minus == 1)
			{
				ft_strncpy(s_pad, s_prec, ft_strlen(s_prec));
				ft_memset(&s_pad[ft_strlen(s_prec)], ' ', opt->width - ft_strlen(s_prec));
			}
			else
			{
				ft_strncpy(&s_pad[opt->width - opt->prec], s_prec, ft_strlen(s_prec));
				ft_memset(s_pad, ' ', opt->width - ft_strlen(s_prec));
			}
			ft_putnstr(s_pad, ft_strlen(s_pad), opt);
			free(s_pad);
			free(s_prec);
		}
		else
		{
			ft_putnstr(s_pad, ft_strlen(s_pad), opt);
		}
	}
	else
	{
		ft_putnstr(temp, ft_strlen(temp), opt);
	}
	return (0);
}

int		print_paddr(t_option *opt, va_list ap)
{
	long long	ll_temp;
	char		*p_temp;
	char		*temp;
	char		*s_pad;
	char		*s_prec;

	ll_temp = (long long)va_arg(ap, long long);
	p_temp = ft_itoa_base_ll(ll_temp, "0123456789abcdef");
	temp = ft_strjoin("0x", p_temp);
	free(p_temp);
	if (opt->prec == 0)
		temp[2] = '\0';
	if (opt->prec > ft_strlen(temp) && opt->prec != -1)
	{
		if (!(s_prec = make_padstr(opt->prec, ' ')))
			return (-1);
		ft_strncpy(s_prec, temp, opt->prec);
		if (opt->width > opt->prec)
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
				ft_strncpy(&s_pad[opt->width - opt->prec], s_prec, ft_strlen(s_prec));
				ft_memset(s_pad, ' ', opt->width - ft_strlen(s_prec));
			}
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
		if (!(s_pad = make_padstr(opt->width, opt->pad)))
			return (-1);
		if (opt->minus == 1)
		{
			ft_strncpy(s_pad, temp, ft_strlen(temp));
		}
		else
			ft_strcpy(&s_pad[opt->width - ft_strlen(temp)], temp);
		if (opt->width > opt->prec && opt->prec > 0)
		{
			if (!(s_prec = make_padstr(opt->prec, ' ')))
				return (-1);
			ft_strncpy(&s_prec[opt->prec - ft_strlen(temp)], temp, opt->prec);
			if (opt->minus == 1)
			{
				ft_strncpy(s_pad, s_prec, ft_strlen(s_prec));
				ft_memset(&s_pad[ft_strlen(s_prec)], ' ', opt->width - ft_strlen(s_prec));
			}
			else
			{
				ft_strncpy(&s_pad[opt->width - opt->prec], s_prec, ft_strlen(s_prec));
				ft_memset(s_pad, ' ', opt->width - ft_strlen(s_prec));
			}
			ft_putnstr(s_pad, ft_strlen(s_pad), opt);
			free(s_pad);
			free(s_prec);
		}
		else
		{
			ft_putnstr(s_pad, ft_strlen(s_pad), opt);
		}
	}
	else
	{
		ft_putnstr(temp, ft_strlen(temp), opt);
	}
	free(temp);
	return (0);

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
		{
			ft_putnstr((char *)&str[i], 1, &opt);
		}
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

