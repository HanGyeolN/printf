/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:54:26 by hna               #+#    #+#             */
/*   Updated: 2020/02/27 01:09:37 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *src, int c)
{
	int		i;
	int		src_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	i = src_len;
	while (i >= 0)
	{
		if (src[i] == (char)c)
			return ((char *)&src[i]);
		i--;
	}
	return (0);
}
