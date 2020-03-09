/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 14:16:22 by hna               #+#    #+#             */
/*   Updated: 2020/02/27 01:09:18 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *str, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*ret;

	i = -1;
	len = ft_strlen((char *)str);
	if (!(ret = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (++i < len)
		ret[i] = f((unsigned int)i, (char)str[i]);
	ret[i] = '\0';
	return (ret);
}
