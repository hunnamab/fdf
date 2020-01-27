/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 16:15:35 by pmetron           #+#    #+#             */
/*   Updated: 2019/09/22 18:18:23 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_delimeters(char const *s, char c)
{
	int num;
	int i;

	num = 0;
	i = 0;
	if (s)
	{
		while (s[i] != '\0')
		{
			if (s[i] != c && s[i + 1] == c)
			{
				num++;
			}
			if (s[i] != c && s[i + 1] == '\0')
			{
				num++;
			}
			i++;
		}
	}
	return (num);
}

static int		ft_strlen_del(int y, char const *s, char c)
{
	int j;

	j = 0;
	if (s)
	{
		while (s[y] != c && s[y] != '\0')
		{
			y++;
			j++;
		}
	}
	return (j);
}

static	char	**ft_free_arr(char **s)
{
	ft_memdel((void **)&s);
	return (s);
}

char			**ft_strsplit(char const *s, char c)
{
	int		num;
	int		i;
	char	**arr;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[i] == c && s[i] != '\0')
		i++;
	num = ft_delimeters(s, c);
	if (!(arr = ft_memalloc(sizeof(char *) * num + 1)))
		return (NULL);
	while (num-- >= 1)
	{
		if (!(arr[j] = ft_strnew(ft_strlen_del(i, s, c))))
			return (ft_free_arr(arr));
		arr[j++] = ft_strsub(s, i, ft_strlen_del(i, s, c));
		i = i + ft_strlen_del(i, s, c);
		while (s[i] == c && s[i])
			i++;
	}
	arr[j] = NULL;
	return (arr);
}
