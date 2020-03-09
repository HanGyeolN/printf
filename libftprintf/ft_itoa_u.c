#include "libft.h"

char	*ft_itoa_u(unsigned int n)
{
	unsigned int	div;
	unsigned int    len;
	char	        *ret;

	div = n;
	len = (n == 0) ? 1 : 0;
	while (div != 0)
	{
		div = div / 10;
		len++;
	}
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (0);
	ret[len] = '\0';
	ret[0] = '0';
	while (n != 0)
	{
		len--;
		ret[len] = (n % 10) + '0';
		n = n / 10;
	}
	return (ret);
}
