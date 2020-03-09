/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:07:41 by hna               #+#    #+#             */
/*   Updated: 2020/02/27 01:09:27 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_len;
	size_t	haystack_len;

	i = 0;
	needle_len = (size_t)ft_strlen((char *)needle);
	haystack_len = (size_t)ft_strlen((char *)haystack);
	if (needle_len == 0)
		return ((char *)haystack);
	if (len < needle_len)
		return (0);
	while (i + needle_len <= len && haystack[i] != '\0')
	{
		if (ft_strncmp(&haystack[i], needle, needle_len) == 0)
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}
