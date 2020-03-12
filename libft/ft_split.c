/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hna <hna@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 01:24:11 by hna               #+#    #+#             */
/*   Updated: 2020/02/27 01:08:32 by hna              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	split_len_idx(char *str, char c, int *s_idx)
{
	int		i;
	int		cnt;
	int		flag;

	i = 0;
	cnt = 0;
	flag = 1;
	while (str[i])
	{
		if (str[i] == c)
			flag = 1;
		else if (str[i] != c && flag == 1)
		{
			if (s_idx)
				s_idx[cnt] = i;
			cnt++;
			flag = 0;
		}
		i++;
	}
	return (cnt);
}

static char	*ft_strsep(char *str, char c)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	len = 0;
	while (str[len] != c && str[len] != '\0')
		len++;
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (0);
	ft_strlcpy(ret, str, len + 1);
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	int		*s_idx;
	int		cnt;
	int		i;

	i = -1;
	cnt = split_len_idx((char *)s, c, 0);
	if (!(s_idx = malloc(sizeof(int) * cnt)))
		return (0);
	split_len_idx((char *)s, c, s_idx);
	if (!(ret = malloc(sizeof(char *) * (cnt + 1))))
	{
		free(s_idx);
		return (0);
	}
	while (++i < cnt)
	{
		ret[i] = ft_strsep((char *)&s[s_idx[i]], c);
		if (!ret[i])
			while (--i >= 0)
				free(ret[i]);
	}
	ret[cnt] = 0;
	free(s_idx);
	return (ret);
}
