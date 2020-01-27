/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmetron <pmetron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 18:18:39 by pmetron           #+#    #+#             */
/*   Updated: 2019/09/22 13:31:24 by pmetron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		reverse(char *c)
{
	size_t	start;
	size_t	finish;
	char	s;

	if (c[0] == '-')
	{
		start = 1;
	}
	else
	{
		start = 0;
	}
	finish = ft_strlen(c) - 1;
	while (start < finish)
	{
		s = c[start];
		c[start] = c[finish];
		c[finish] = s;
		start++;
		finish--;
	}
}

static int		dec(int n)
{
	int i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10 != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static	void	check_sign(char *s, int n)
{
	int sign;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
	}
	if (sign == 1)
	{
		s[0] = '-';
	}
}

static	char	*min_char(char *a)
{
	a[0] = '-';
	a[1] = '2';
	a[2] = '1';
	a[3] = '4';
	a[4] = '7';
	a[5] = '4';
	a[6] = '8';
	a[7] = '3';
	a[8] = '6';
	a[9] = '4';
	a[10] = '8';
	a[11] = '\0';
	return (a);
}

char			*ft_itoa(int n)
{
	size_t	i;
	char	*c;

	i = 0;
	c = NULL;
	if ((c = ft_strnew(dec(n))))
	{
		if (n == -2147483648)
			return (min_char(c));
		check_sign(c, n);
		if (c[0] == '-')
		{
			n = -n;
			i = 1;
		}
		while ((n / 10) > 0)
		{
			c[i++] = n % 10 + '0';
			n = n / 10;
		}
		c[i] = n + '0';
		reverse(c);
	}
	return (c);
}
