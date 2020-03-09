/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:24:24 by hna               #+#    #+#             */
/*   Updated: 2020/03/05 13:31:07 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(unsigned int n, const char *base)
{
	unsigned int	div;
	unsigned int	len;
	unsigned int	base_len;
	char			*ret;

	div = n;
	len = (n == 0) ? 1 : 0;
	base_len = (unsigned int)ft_strlen((char *)base);
	while (div != 0)
	{
		div = div / base_len;
		len++;
	}
	if (!(ret = calloc((len + 1), sizeof(char))))
		return (0);
	ret[0] = '0';
	while (n != 0)
	{
		len--;
		ret[len] = base[(n % base_len)];
		n = n / base_len;
	}
	return (ret);
}
