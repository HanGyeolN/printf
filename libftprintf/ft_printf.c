#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
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
	if (ft_strchr("cspdiuxX", c))
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

int		ft_printf(const char *str, ...)
{
	va_list		ap;
	int			i;
	int			ret;
	char		res[10000];
	char		*temp;
	int			width;
	char		pad;
	char		*padding;
	int			minus;
	int			prec;
	unsigned int	u_temp;
	char		c_temp;
	int			n_temp;
	long long	ll_temp;
	char		*p_temp;
	char		*str_prec;
	char		*tmp_prec;

	ft_memset((void *)res, 0, 10000);
	va_start(ap, str);
	width = -1;
	i = 0;
	pad = ' ';
	minus = -1;
	prec = -1;
	if (str == 0)
		return (-1);
	while (str[i])
	{
		if (str[i] == '%')
		{
			width = -1;
			pad = ' ';
			minus = -1;
			prec = -1;
			if (str[i + 1] == '%')
			{
				ft_strncat(res, (char *)&str[i], 1);
				i += 2;
				continue ;
			}
			while (!is_conv(str[i]))
			{
				if (str[i] == '\0')
				{
					return (-1);
				}
				else if (str[i] == '0')
				{
					pad = '0';
					i++;
				}
				else if (str[i] == '-')
				{
					minus = 1;
					i++;
				}
				else if (str[i] == '*')
				{
					width = va_arg(ap, int);
					if (!(padding = malloc(sizeof(char) * (width + 1))))
						return (-1);
					ft_memset(padding, pad, width);
					padding[width] = '\0';
					i++;
				}
				else if (str[i] == '.')
				{
					i++;
					prec = 0;
					if (is_numeric(str[i]))
					{
						prec = ft_atoi(&str[i]);
						if (!(str_prec = calloc((prec + 1), sizeof(char))))
							return (0);
						ft_memset(str_prec, '0', prec);
						while (is_numeric(str[i]))
							i++;
					}
					else if (str[i] == '*')
					{
						prec = va_arg(ap, int);
						if (!(str_prec = calloc((prec + 1), sizeof(char))))
							return (0);
						ft_memset(str_prec, '0', prec);
						i++;
					}
				}
				else if (is_numeric(str[i]))
				{
					width = ft_atoi(&str[i]);
					if (!(padding = malloc(sizeof(char) * (width + 1))))
						return (0);
					ft_memset(padding, pad, width);
					padding[width] = '\0';
					while (is_numeric(str[i]))
						i++;
				}
				else
					i++;
			}
			if (str[i] == 'd' || str[i] == 'i')
			{
				n_temp = (int)va_arg(ap, int);
				temp = ft_itoa(n_temp);
				if (prec > ft_strlen(temp))
				{
					if (temp[0] == '-')
					{
						ft_strncpy(&str_prec[prec - ft_strlen(temp) + 1], &temp[1], ft_strlen(temp));
						tmp_prec = malloc(sizeof(char) * (ft_strlen(str_prec) + 2));
						tmp_prec[0] = '-';
						ft_strcpy(&tmp_prec[1], str_prec);
						tmp_prec[prec + 1] = '\0';
						free(str_prec);
						str_prec = tmp_prec;
					}
					else
						ft_strncpy(&str_prec[prec - ft_strlen(temp)], temp, ft_strlen(temp));
					if (width > prec)
					{
						if (minus == 1)
						{
							ft_strncpy(padding, str_prec, ft_strlen(str_prec));
							ft_memset(&padding[ft_strlen(str_prec)], ' ', width - ft_strlen(str_prec));
						}
						else
						{
							if (temp[0] == '-')
								ft_strncpy(&padding[width - prec - 1], str_prec, ft_strlen(str_prec));
							else
								ft_strncpy(&padding[width - prec], str_prec, ft_strlen(str_prec));
							if (temp[0] == '-')
								ft_memset(padding, ' ', width - ft_strlen(str_prec));
							else
								ft_memset(padding, ' ', width - ft_strlen(str_prec));
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
				else if (width > ft_strlen(temp))
				{
					if (minus == 1)
					{
						free(padding);
						if (!(padding = malloc(sizeof(char) * (width + 1))))
							return (-1);
						ft_memset(padding, ' ', width);
						padding[width] = '\0';
						ft_strncpy(padding, temp, ft_strlen(temp));
					}
					else
						ft_strcpy(&padding[width - ft_strlen(temp)], temp);
					if (temp[0] == '-' && padding[0] == '0')
					{
						padding[width - ft_strlen(temp)] = '0';
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
			}
			else if (str[i] == 'u')
			{
				u_temp = (unsigned int)va_arg(ap, int);
				temp = ft_itoa_u(u_temp);
				if (prec > ft_strlen(temp))
				{
					ft_strncpy(&str_prec[prec - ft_strlen(temp)], temp, ft_strlen(temp));
					if (width > prec)
					{
						if (minus == 1)
							ft_strncpy(padding, str_prec, ft_strlen(str_prec));
						else
							ft_strncpy(&padding[width - prec], str_prec, ft_strlen(str_prec));
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
				else if (width > ft_strlen(temp))
				{
					if (minus == 1)
						ft_strncpy(padding, temp, ft_strlen(temp));
					else
						ft_strcpy(&padding[width - ft_strlen(temp)], temp);
					ft_strncat(res, padding, ft_strlen(padding));
					free(padding);
				}
				else
				{
					ft_strncat(res, temp, ft_strlen(temp));
				}
				free(temp);
			}
			else if (str[i] == 'c')
			{
				c_temp = (char)va_arg(ap, int);
				temp = malloc(sizeof(char) * 2);
				temp[0] = c_temp;
				temp[1] = '\0';
				if (prec > ft_strlen(temp))
				{
					ft_strncpy(&str_prec[prec - ft_strlen(temp)], temp, ft_strlen(temp));
					if (width > prec)
					{
						if (minus == 1)
							ft_strncpy(padding, str_prec, ft_strlen(str_prec));
						else
							ft_strncpy(&padding[width - prec], str_prec, ft_strlen(str_prec));
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
				else if (width > ft_strlen(temp))
				{
					if (minus == 1)
						ft_strncpy(padding, temp, ft_strlen(temp));
					else
						ft_strcpy(&padding[width - ft_strlen(temp)], temp);
					ft_strncat(res, padding, ft_strlen(padding));
					free(padding);
				}
				else
				{
					ft_strncat(res, temp, ft_strlen(temp));
				}
				free(temp);
			}
			else if (str[i] == 'x' || str[i] == 'X')
			{
				n_temp = (int)va_arg(ap, int);
				if (n_temp < 0)
					u_temp = n_temp;
				if (str[i] == 'x')
					temp = ft_itoa_base(n_temp, "0123456789abcdef");
				else
					temp = ft_itoa_base(n_temp, "0123456789ABCDEF");
				if (prec > ft_strlen(temp))
				{
					ft_strncpy(&str_prec[prec - ft_strlen(temp)], temp, ft_strlen(temp));
					if (width > prec)
					{
						if (minus == 1)
						{
							ft_strncpy(padding, str_prec, ft_strlen(str_prec));
							ft_memset(&padding[ft_strlen(str_prec)], ' ', width - ft_strlen(str_prec));
						}
						else
						{
							ft_strncpy(&padding[width - prec], str_prec, ft_strlen(str_prec));
							ft_memset(padding, ' ', width - ft_strlen(str_prec));
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
				else if (width > ft_strlen(temp))
				{
					if (minus == 1)
						ft_strncpy(padding, temp, ft_strlen(temp));
					else
						ft_strcpy(&padding[width - ft_strlen(temp)], temp);
					if (width > prec && prec != -1)
					{
						ft_strncpy(&str_prec[prec - ft_strlen(temp)], temp, ft_strlen(temp));
						if (minus == 1)
						{
							ft_strncpy(padding, str_prec, ft_strlen(str_prec));
							ft_memset(&padding[ft_strlen(str_prec)], ' ', width - ft_strlen(str_prec));
						}
						else
						{
							ft_strncpy(&padding[width - prec], str_prec, ft_strlen(str_prec));
							ft_memset(padding, ' ', width - ft_strlen(str_prec));
						}
						ft_strncat(res, padding, ft_strlen(padding));
						free(padding);
						free(str_prec);
					}
					else
					{
						ft_strncat(res, padding, ft_strlen(padding));
						free(padding);
					}
				}
				else
				{
					ft_strncat(res, temp, ft_strlen(temp));
				}
				free(temp);
			}
			else if (str[i] == 's')
			{
				temp = (char *)va_arg(ap, char *);
				if (temp == 0)
				{
					temp = malloc(sizeof(char) * 7);
					ft_strcpy(temp, "(null)");
				}
				if (prec < ft_strlen(temp) && prec > 0)
				{
					ft_strncpy(str_prec, temp, prec);
					if (width > prec)
					{
						if (minus == 1)
						{
							ft_strncpy(padding, str_prec, ft_strlen(str_prec));
							ft_memset(&padding[ft_strlen(str_prec)], ' ', width - ft_strlen(str_prec));
						}
						else
						{
							ft_strncpy(&padding[width - prec], str_prec, ft_strlen(str_prec));
							ft_memset(padding, ' ', width - ft_strlen(str_prec));
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
				else if (width > ft_strlen(temp))
				{
					if (minus == 1)
					{
						free(padding);
						if (!(padding = malloc(sizeof(char) * (width + 1))))
							return (-1);
						ft_memset(padding, ' ', width);
						padding[width] = '\0';
						ft_strncpy(padding, temp, ft_strlen(temp));
					}
					else
						ft_strcpy(&padding[width - ft_strlen(temp)], temp);
					if (width > prec && prec > 0)
					{
						ft_strncpy(&str_prec[prec - ft_strlen(temp)], temp, prec);
						if (minus == 1)
						{
							ft_strncpy(padding, str_prec, ft_strlen(str_prec));
							ft_memset(&padding[ft_strlen(str_prec)], ' ', width - ft_strlen(str_prec));
						}
						else
						{
							ft_strncpy(&padding[width - prec], str_prec, ft_strlen(str_prec));
							ft_memset(padding, ' ', width - ft_strlen(str_prec));
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
			}
			else if (str[i] == 'p')
			{
				ll_temp = (long long)va_arg(ap, long long);
				p_temp = ft_itoa_base_ll(ll_temp, "0123456789abcdef");
				temp = ft_strjoin("0x", p_temp);
				free(p_temp);
				if (prec > ft_strlen(temp))
				{
					ft_strncpy(&str_prec[prec - ft_strlen(temp)], temp, ft_strlen(temp));
					if (width > prec)
					{
						if (minus == 1)
							ft_strncpy(padding, str_prec, ft_strlen(str_prec));
						else
							ft_strncpy(&padding[width - prec], str_prec, ft_strlen(str_prec));
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
				else if (width > ft_strlen(temp))
				{
					if (minus == 1)
						ft_strncpy(padding, temp, ft_strlen(temp));
					else
						ft_strcpy(&padding[width - ft_strlen(temp)], temp);
					ft_strncat(res, padding, ft_strlen(padding));
					free(padding);
				}
				else
				{
					ft_strncat(res, temp, ft_strlen(temp));
				}
				free(temp);
			}
		}
		else
			ft_strncat(res, (char *)&str[i], 1);
		i++;
	}
	ft_putstr(res);
	ret = ft_strlen(res);
	va_end(ap);
	return (ret);
}