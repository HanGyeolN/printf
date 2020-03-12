/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:24:18 by hna               #+#    #+#             */
/*   Updated: 2020/02/27 01:08:51 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		src_len;
	char	*ret;

	src_len = ft_strlen((char *)src);
	ret = malloc(sizeof(char) * (src_len + 1));
	ft_strlcpy(ret, src, (size_t)(src_len + 1));
	return (ret);
}
