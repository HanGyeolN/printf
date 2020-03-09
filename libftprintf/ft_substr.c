/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:56:04 by hna               #+#    #+#             */
/*   Updated: 2020/02/27 01:09:49 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	str_len;
	size_t	size;
	char	*ret;

	str_len = (size_t)ft_strlen((char *)str);
	if (start > str_len)
		return (0);
	if (len + start >= str_len + 1)
		size = str_len - start + 1;
	else
		size = len + 1;
	ret = malloc(sizeof(char) * size);
	if (!ret)
		return (0);
	ft_strlcpy(ret, &str[start], size);
	return (ret);
}
