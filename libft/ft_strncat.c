/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:52:24 by hna               #+#    #+#             */
/*   Updated: 2020/01/27 22:31:44 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int i;
	unsigned int dest_len;

	i = 0;
	dest_len = (unsigned int)ft_strlen(dest);
	while (src[i] != '\0' && i < nb)
	{
		dest[i + dest_len] = src[i];
		i++;
	}
	dest[i + dest_len] = '\0';
	return (dest);
}
