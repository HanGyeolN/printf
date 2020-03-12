/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 00:26:43 by hna               #+#    #+#             */
/*   Updated: 2020/02/29 05:11:29 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		s1_len;
	size_t	set_len;
	char	*ret;

	i = 0;
	s1_len = ft_strlen((char *)s1);
	set_len = (size_t)ft_strlen((char *)set);
	if (!(ret = malloc(sizeof(char) * (s1_len + 1))))
		return (0);
	ft_strlcpy(ret, s1, (s1_len + 1));
	if (s1_len == 0)
		return (ret);
	while (ft_memchr((void *)set, ret[i], set_len) != 0)
		i++;
	ft_memmove(ret, ret + i, s1_len - i);
	i++;
	while (--i > 0)
		ret[--s1_len] = '\0';
	while (ft_memchr((void *)set, ret[--s1_len], set_len) != 0)
		ret[s1_len] = '\0';
	return (ret);
}
