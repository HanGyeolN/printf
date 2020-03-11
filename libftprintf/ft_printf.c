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

int		next_is_percent(const char *str, char *res, int *idx)
{
	if (str[*idx + 1] == '%')
	{
		ft_strncat(res, "%", 1);
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

int		concat_perc(t_option *opt, char *res)
{
	unsigned char	c_temp;
	char			*temp;
	char			*padding;
	char			*str_prec;

	c_temp = '%';
	temp = malloc(sizeof(char) * 2);
	temp[0] = c_temp;
	temp[1] = '\0';
	if (opt->prec > ft_strlen(temp))
	{
		if (!(str_prec = make_padstr(opt->prec, '0')))
			return (-1);
		ft_strncpy(&str_prec[opt->prec - ft_strlen(temp)], temp, 1);
		if (opt->width > opt->prec)
		{
			if (!(padding = make_padstr(opt->width, opt->pad)))
				return (-1);
			if (opt->minus == 1)
				ft_strncpy(padding, str_prec, ft_strlen(str_prec));
			else
				ft_strncpy(&padding[opt->width - opt->prec], str_prec, ft_strlen(str_prec));
			ft_strncat(res, padding, ft_strlen(padding));
			free(padding);
			free(str_prec);
		}
		else
		{				
			ft_strncat(res, str_prec, ft_strlen(str_prec));
			free(str_prec);
		}
	}
	else if (opt->width > ft_strlen(temp))
	{
		if (opt->minus == 1)
			opt->pad = ' ';
		if (!(padding = make_padstr(opt->width, opt->pad)))
			return (-1);
		if (opt->minus == 1)
			ft_strncpy(padding, temp, ft_strlen(temp));
		else
			ft_strcpy(&padding[opt->width - ft_strlen(temp)], temp);
		ft_strncat(res, padding, ft_strlen(padding));
		free(padding);
	}
	else
	{
		ft_strncat(res, temp, ft_strlen(temp));
	}
	free(temp);
	return (0);
}

int		concat_int(t_option *opt, va_list ap, char *res)
{
	int		n_temp;
	char	*temp;
	char	*padding;
	char	*str_prec;
	char	*tmp_prec;

	n_temp = (int)va_arg(ap, int);
	temp = ft_itoa(n_temp);
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
	if ((opt->prec > ft_strlen(temp) && temp[0] != '-' ) || (opt->prec > ft_strlen(temp) - 1 && temp[0] == '-'))
	{
		if (!(str_prec = make_padstr(opt->prec, '0')))
			return (-1);
		if (temp[0] == '-')
		{
			ft_strncpy(&str_prec[opt->prec - ft_strlen(temp) + 1], &temp[1], ft_strlen(temp));
			tmp_prec = malloc(sizeof(char) * (ft_strlen(str_prec) + 2));
			tmp_prec[0] = '-';
			ft_strcpy(&tmp_prec[1], str_prec);
			tmp_prec[opt->prec + 1] = '\0';
			free(str_prec);
			str_prec = tmp_prec;
		}
		else
			ft_strncpy(&str_prec[opt->prec - ft_strlen(temp)], temp, ft_strlen(temp));
		if (opt->width > opt->prec)
		{
			if (!(padding = make_padstr(opt->width, opt->pad)))
				return (-1);
			if (opt->minus == 1)
			{
				ft_strncpy(padding, str_prec, ft_strlen(str_prec));
				ft_memset(&padding[ft_strlen(str_prec)], ' ', opt->width - ft_strlen(str_prec));
			}
			else
			{
				if (temp[0] == '-')
					ft_strncpy(&padding[opt->width - opt->prec - 1], str_prec, ft_strlen(str_prec));
				else
					ft_strncpy(&padding[opt->width - opt->prec], str_prec, ft_strlen(str_prec));
				if (temp[0] == '-')
					ft_memset(padding, ' ', opt->width - ft_strlen(str_prec));
				else
					ft_memset(padding, ' ', opt->width - ft_strlen(str_prec));
			}
			ft_strncat(res, padding, ft_strlen(padding));
			free(padding);
			free(str_prec);
		}
		else
		{				
			ft_strncat(res, str_prec, ft_strlen(str_prec));
			free(str_prec);
		}
	}
	else if (opt->width > ft_strlen(temp))
	{
		if (opt->prec != -1 && opt->prec <= ft_strlen(temp))
		{
			if (!(padding = make_padstr(opt->width, ' ')))
				return (-1);
		}
		else
		{
			if (!(padding = make_padstr(opt->width, opt->pad)))
				return (-1);
		}
		if (opt->minus == 1)
		{
			free(padding);
			if (!(padding = make_padstr(opt->width, ' ')))
				return (-1);
			ft_strncpy(padding, temp, ft_strlen(temp));
		}
		else
			ft_strcpy(&padding[opt->width - ft_strlen(temp)], temp);
		if (temp[0] == '-' && padding[0] == '0')
		{
			padding[opt->width - ft_strlen(temp)] = '0';
			padding[0] = '-';
		}
		ft_strncat(res, padding, ft_strlen(padding));
		free(padding);
	}
	else
	{
		ft_strncat(res, temp, ft_strlen(temp));
	}
	free(temp);
	return (0);
}

int		concat_uint(t_option *opt, va_list ap, char *res)
{
	unsigned int	u_temp;
	char			*temp;
	char			*padding;
	char			*str_prec;

	u_temp = (unsigned int)va_arg(ap, int);
	temp = ft_itoa_u(u_temp);
	if (opt->prec == 0)
		temp[0] = '\0';
	if (opt->prec > ft_strlen(temp))
	{
		if (!(str_prec = make_padstr(opt->prec, '0')))
			return (-1);
		ft_strncpy(&str_prec[opt->prec - ft_strlen(temp)], temp, ft_strlen(temp));
		if (opt->width > opt->prec)
		{
			opt->pad = ' ';
			if (!(padding = make_padstr(opt->width, opt->pad)))
				return (-1);
			if (opt->minus == 1)
				ft_strncpy(padding, str_prec, ft_strlen(str_prec));
			else
				ft_strncpy(&padding[opt->width - opt->prec], str_prec, ft_strlen(str_prec));
			ft_strncat(res, padding, ft_strlen(padding));
			free(padding);
			free(str_prec);
		}
		else
		{				
			ft_strncat(res, str_prec, ft_strlen(str_prec));
			free(str_prec);
		}
	}
	else if (opt->width > ft_strlen(temp))
	{
		if (opt->prec != -1 && opt->prec < ft_strlen(temp))
		{
			if (!(padding = make_padstr(opt->width, ' ')))
				return (-1);
		}
		else
		{
			if (!(padding = make_padstr(opt->width, opt->pad)))
				return (-1);
		}
		if (opt->minus == 1)
			ft_strncpy(padding, temp, ft_strlen(temp));
		else
			ft_strcpy(&padding[opt->width - ft_strlen(temp)], temp);
		ft_strncat(res, padding, ft_strlen(padding));
		free(padding);
	}
	else
	{
		ft_strncat(res, temp, ft_strlen(temp));
	}
	free(temp);
	return (0);
}

int		concat_char(t_option *opt, va_list ap, char *res)
{
	unsigned char	c_temp;
	char			*temp;
	char			*padding;
	char			*str_prec;

	c_temp = (char)va_arg(ap, int);
	temp = malloc(sizeof(char) * 2);
	if (c_temp == 0)
		write(1, &c_temp, 1);
	temp[0] = c_temp;
	temp[1] = '\0';
	if (opt->prec > ft_strlen(temp))
	{
		if (!(str_prec = make_padstr(opt->prec, '0')))
			return (-1);
		ft_strncpy(&str_prec[opt->prec - ft_strlen(temp)], temp, 1);
		if (opt->width > opt->prec)
		{
			if (!(padding = make_padstr(opt->width, opt->pad)))
				return (-1);
			if (opt->minus == 1)
				ft_strncpy(padding, str_prec, ft_strlen(str_prec));
			else
				ft_strncpy(&padding[opt->width - opt->prec], str_prec, ft_strlen(str_prec));
			ft_strncat(res, padding, ft_strlen(padding));
			free(padding);
			free(str_prec);
		}
		else
		{				
			ft_strncat(res, str_prec, ft_strlen(str_prec));
			free(str_prec);
		}
	}
	else if (opt->width > ft_strlen(temp))
	{
		if (!(padding = make_padstr(opt->width, opt->pad)))
			return (-1);
		if (opt->minus == 1)
			ft_strncpy(padding, temp, ft_strlen(temp));
		else
			ft_strcpy(&padding[opt->width - ft_strlen(temp)], temp);
		ft_strncat(res, padding, ft_strlen(padding));
		free(padding);
	}
	else
	{
		ft_strncat(res, temp, 1);
	}
	free(temp);
	return (0);
}

int		concat_hex(t_option *opt, va_list ap, char *res, char mode)
{
	int		n_temp;
	int		u_temp;
	char	*temp;
	char	*padding;
	char	*str_prec;

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
		if (!(str_prec = make_padstr(opt->prec, '0')))
			return (-1);
		ft_strncpy(&str_prec[opt->prec - ft_strlen(temp)], temp, ft_strlen(temp));
		if (opt->width > opt->prec)
		{
			if (!(padding = make_padstr(opt->width, opt->pad)))
				return (-1);
			if (opt->minus == 1)
			{
				ft_strncpy(padding, str_prec, ft_strlen(str_prec));
				ft_memset(&padding[ft_strlen(str_prec)], ' ', opt->width - ft_strlen(str_prec));
			}
			else
			{
				ft_strncpy(&padding[opt->width - opt->prec], str_prec, ft_strlen(str_prec));
				ft_memset(padding, ' ', opt->width - ft_strlen(str_prec));
			}
			ft_strncat(res, padding, ft_strlen(padding));
			free(padding);
			free(str_prec);
		}
		else
		{				
			ft_strncat(res, str_prec, ft_strlen(str_prec));
			free(str_prec);
		}
	}
	else if (opt->width > ft_strlen(temp))
	{
		if (opt->prec < ft_strlen(temp) && opt->prec != -1)
			opt->pad = ' ';
		if (!(padding = make_padstr(opt->width, opt->pad)))
			return (-1);
		if (opt->minus == 1)
			ft_strncpy(padding, temp, ft_strlen(temp));
		else
			ft_strcpy(&padding[opt->width - ft_strlen(temp)], temp);
		ft_strncat(res, padding, ft_strlen(padding));
		free(padding);
	}
	else
	{
		ft_strncat(res, temp, ft_strlen(temp));
	}
	free(temp);
	return (0);
}

int		concat_str(t_option *opt, va_list ap, char *res)
{
	char	*temp;
	char	*padding;
	char	*str_prec;

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
		if (!(str_prec = make_padstr(opt->prec, ' ')))
			return (-1);
		ft_strncpy(str_prec, temp, opt->prec);
		if (opt->width > opt->prec)
		{
			if (!(padding = make_padstr(opt->width, opt->pad)))
				return (-1);
			if (opt->minus == 1)
			{
				ft_strncpy(padding, str_prec, ft_strlen(str_prec));
				ft_memset(&padding[ft_strlen(str_prec)], ' ', opt->width - ft_strlen(str_prec));
			}
			else
			{
				ft_strncpy(&padding[opt->width - opt->prec], str_prec, ft_strlen(str_prec));
				ft_memset(padding, ' ', opt->width - ft_strlen(str_prec));
			}
			ft_strncat(res, padding, ft_strlen(padding));
			free(padding);
			free(str_prec);
		}
		else
		{				
			ft_strncat(res, str_prec, ft_strlen(str_prec));
			free(str_prec);
		}
	}
	else if (opt->width > ft_strlen(temp))
	{
		if (!(padding = make_padstr(opt->width, opt->pad)))
			return (-1);
		if (opt->minus == 1)
		{
			free(padding);
			if (!(padding = make_padstr(opt->width, ' ')))
				return (-1);
			ft_strncpy(padding, temp, ft_strlen(temp));
		}
		else
			ft_strcpy(&padding[opt->width - ft_strlen(temp)], temp);
		if (opt->width > opt->prec && opt->prec > 0 && opt->prec < ft_strlen(temp))
		{
			if (!(str_prec = make_padstr(opt->prec, ' ')))
				return (-1);
			ft_strncpy(&str_prec[opt->prec - ft_strlen(temp)], temp, opt->prec);
			if (opt->minus == 1)
			{
				ft_strncpy(padding, str_prec, ft_strlen(str_prec));
				ft_memset(&padding[ft_strlen(str_prec)], ' ', opt->width - ft_strlen(str_prec));
			}
			else
			{
				ft_strncpy(&padding[opt->width - opt->prec], str_prec, ft_strlen(str_prec));
				ft_memset(padding, ' ', opt->width - ft_strlen(str_prec));
			}
			ft_strncat(res, padding, ft_strlen(padding));
			free(padding);
			free(str_prec);
		}
		else
		{
			ft_strncat(res, padding, ft_strlen(padding));
		}
	}
	else
	{
		ft_strncat(res, temp, ft_strlen(temp));
	}
	return (0);
}

int		concat_paddr(t_option *opt, va_list ap, char *res)
{
	long long	ll_temp;
	char		*p_temp;
	char		*temp;
	char		*padding;
	char		*str_prec;

	ll_temp = (long long)va_arg(ap, long long);
	p_temp = ft_itoa_base_ll(ll_temp, "0123456789abcdef");
	temp = ft_strjoin("0x", p_temp);
	free(p_temp);
	if (opt->prec == 0)
		temp[2] = '\0';
	if (opt->prec > ft_strlen(temp) && opt->prec != -1)
	{
		if (!(str_prec = make_padstr(opt->prec, ' ')))
			return (-1);
		ft_strncpy(str_prec, temp, opt->prec);
		if (opt->width > opt->prec)
		{
			if (!(padding = make_padstr(opt->width, opt->pad)))
				return (-1);
			if (opt->minus == 1)
			{
				ft_strncpy(padding, str_prec, ft_strlen(str_prec));
				ft_memset(&padding[ft_strlen(str_prec)], ' ', opt->width - ft_strlen(str_prec));
			}
			else
			{
				ft_strncpy(&padding[opt->width - opt->prec], str_prec, ft_strlen(str_prec));
				ft_memset(padding, ' ', opt->width - ft_strlen(str_prec));
			}
			ft_strncat(res, padding, ft_strlen(padding));
			free(padding);
			free(str_prec);
		}
		else
		{				
			ft_strncat(res, str_prec, ft_strlen(str_prec));
			free(str_prec);
		}
	}
	else if (opt->width > ft_strlen(temp))
	{
		if (!(padding = make_padstr(opt->width, opt->pad)))
			return (-1);
		if (opt->minus == 1)
		{
			ft_strncpy(padding, temp, ft_strlen(temp));
		}
		else
			ft_strcpy(&padding[opt->width - ft_strlen(temp)], temp);
		if (opt->width > opt->prec && opt->prec > 0)
		{
			if (!(str_prec = make_padstr(opt->prec, ' ')))
				return (-1);
			ft_strncpy(&str_prec[opt->prec - ft_strlen(temp)], temp, opt->prec);
			if (opt->minus == 1)
			{
				ft_strncpy(padding, str_prec, ft_strlen(str_prec));
				ft_memset(&padding[ft_strlen(str_prec)], ' ', opt->width - ft_strlen(str_prec));
			}
			else
			{
				ft_strncpy(&padding[opt->width - opt->prec], str_prec, ft_strlen(str_prec));
				ft_memset(padding, ' ', opt->width - ft_strlen(str_prec));
			}
			ft_strncat(res, padding, ft_strlen(padding));
			free(padding);
			free(str_prec);
		}
		else
		{
			ft_strncat(res, padding, ft_strlen(padding));
		}
	}
	else
	{
		ft_strncat(res, temp, ft_strlen(temp));
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

int		convert_conv(char conv, t_option *opt, va_list ap, char *res)
{
	if (conv == 'd' || conv == 'i')
		concat_int(opt, ap, res);
	else if (conv == 'u')
		concat_uint(opt, ap, res);
	else if (conv == 'c')
		concat_char(opt, ap, res);
	else if (conv == 'x' || conv == 'X')
		concat_hex(opt, ap, res, conv);
	else if (conv == 's')
		concat_str(opt, ap, res);
	else if (conv == 'p')
		concat_paddr(opt, ap, res);
	else if (conv == '%')
		concat_perc(opt, res);
	return (0);
}

int		convert_str(char *str, va_list ap, char *res)
{
	int			i;
	t_option	opt;

	i = 0;
	init_option(&opt);
	if (str == 0)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			init_option(&opt);
			if (next_is_percent(str, res, &i))
				continue ;
			if (parse_flag(&opt, ap, (char *)str, &i) == -1)
				return (-1);
			if (convert_conv(str[i], &opt, ap, res) == -1)
				return (-1);
		}
		else
			ft_strncat(res, (char *)&str[i], 1);
		i++;
	}
	return (0);
}

int		ft_printf(const char *str, ...)
{
	va_list		ap;
	int			ret;
	char		res[10000];

	ft_memset((void *)res, 0, 10000);
	va_start(ap, str);
	if (convert_str((char *)str, ap, res) == -1)
		return (-1);
	ft_putstr(res);
	ret = ft_strlen(res);
	va_end(ap);
	return (ret);
}
