/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 23:51:49 by hna               #+#    #+#             */
/*   Updated: 2020/02/27 01:07:35 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*ptr_src;
	unsigned char	*ptr_dst;

	ptr_src = src;
	ptr_dst = dst;
	while (n-- > 0)
		ptr_dst[n] = ptr_src[n];
	return (dst);
}
