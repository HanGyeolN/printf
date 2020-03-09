/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:19:05 by hna               #+#    #+#             */
/*   Updated: 2020/02/06 11:39:12 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlen_ud(char *src)
{
	unsigned int len;

	len = 0;
	while (src[len])
		len++;
	return (len);
}

char			*ft_strstr(char *str, char *to_find)
{
	unsigned int	i;
	unsigned int	find_len;
	unsigned int	str_len;
	int				res;

	i = 0;
	find_len = ft_strlen_ud(to_find);
	str_len = ft_strlen_ud(str);
	if (to_find[0] == '\0')
		return (str);
	while (str[i] != '\0' && i <= find_len - str_len)
	{
		res = ft_strncmp(str + i, to_find, find_len);
		if (res == 0)
			return (str + i);
		i++;
	}
	return (0);
}
