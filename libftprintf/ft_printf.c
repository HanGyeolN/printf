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

int		ft_printf(const char *str, ...)
{
	va_list		ap;
	int			i;
	int			ret;
	char		res[1000];
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

	ft_memset((void *)res, 0, 1000);
	va_start(ap, str);
	width = 0;
	i = 0;
	pad = ' ';
	minus = 0;
	prec = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '%')
			{
				ft_strncat(res, (char *)&str[i], 1);
				i += 2;
				continue ;
			}
			while (!is_conv(str[i]))
			{
				if (str[i] == '0')
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
					i++;
				}
				else if (str[i] == '.')
				{
					i++;
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
				temp = ft_itoa((int)va_arg(ap, int));
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
				temp = ft_itoa_base(n_temp, "0123456789abcdef");
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
			else if (str[i] == 's')
			{
				temp = (char *)va_arg(ap, char *);
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
/*
void	test_d(char *s, int num)
{
	int		ret;

	ret = ft_printf(s, num);
	printf("ret: %d\n", ret);
	ret = printf(s, num);
	printf("ret: %d\n", ret);
	printf("====================\n");
}

void	test_s(char *s, char *s1)
{
	int		ret;

	ret = ft_printf(s, s1);
	printf("ret: %d\n", ret);
	ret = printf(s, s1);
	printf("ret: %d\n", ret);
	printf("====================\n");
}


void	test_d2(char *s, int n1, int n2)
{
	int		ret;

	ret = ft_printf(s, n1, n2);
	printf("ret: %d\n", ret);
	ret = printf(s, n1, n2);
	printf("ret: %d\n", ret);
	printf("====================\n");
}

void	test_p(char *s, void *p)
{
	int		ret;

	ret = ft_printf(s, p);
	printf("ret: %d\n", ret);
	ret = printf(s, p);
	printf("ret: %d\n", ret);
	printf("====================\n");
}

int		main(void)
{
	int		p;

	test_d("test %10d.\n", 1000);
	test_d("test %d\n", 32);
	test_d("%d\n", 42);
	test_d("%dd\n", 55);
	test_d("%%d\n", 10);
	test_d2("%d|%i\n", 31, 32);

	printf("unsigned int\n");
	test_d("test %u.\n", -42);
	test_d("%-20u", -11);

	printf("char test \n");
	test_d("test %-4c.\n", 'g');

	printf("x X test\n");
	test_d("test %x.\n", -255);
	test_d("test %-10x.\n", 0);
	test_d("test %10x.\n", -255);

	printf("s Test\n");
	test_s("hello %s.\n", "world");
	test_s("hello %30s.\n", "world");

	printf("p test\n");
	test_p("test %p.\n", &p);

	printf(". test\n");
	test_d("%.5d\n", 421);
	test_d("%.2d\n", 421);
	test_d("%10.4d\n", 42);
	test_d("%-10.4d\n", 42);
	//ft_printf("test 100%%\n");
	//printf("test 100%%\n");
	return (0);
}
*/
