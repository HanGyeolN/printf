/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 00:57:09 by hna               #+#    #+#             */
/*   Updated: 2020/02/27 01:07:14 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*ptr_dst;
	const unsigned char	*ptr_src;
	size_t				i;

	ptr_dst = dst;
	ptr_src = src;
	i = 0;
	while (i < n && ptr_src[i] != c)
	{
		ptr_dst[i] = ptr_src[i];
		i++;
	}
	if (i < n)
	{
		ptr_dst[i] = ptr_src[i];
		i++;
		return (&ptr_dst[i]);
	}
	return (0);
}
