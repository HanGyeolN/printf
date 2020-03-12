/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 12:58:41 by hna               #+#    #+#             */
/*   Updated: 2020/02/27 01:06:15 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		div;
	int		len;
	char	*ret;

	div = n;
	len = (n <= 0) ? 1 : 0;
	while (div != 0)
	{
		div = div / 10;
		len++;
	}
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (0);
	ret[len] = '\0';
	if (n <= 0)
		ret[0] = (n == 0) ? '0' : '-';
	while (n != 0)
	{
		len--;
		ret[len] = (n > 0) ? (n % 10) + '0' : -(n % 10) + '0';
		n = n / 10;
	}
	return (ret);
}
