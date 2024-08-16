/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 10:17:09 by epolkhov          #+#    #+#             */
/*   Updated: 2023/11/15 17:19:46 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_len(long c)
{
	size_t	len;

	len = 0;
	if (c <= 0)
	{
		len = 1;
		c = c * -1;
	}
	while (c > 0)
	{
		len++;
		c = c / 10;
	}
	return (len);
}

static int	ft_sign(int n)
{
	int	sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	return (sign);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				length;
	int				sign;

	sign = ft_sign(n);
	length = num_len(n);
	str = (char *)malloc(sizeof(char) * (length + 1));
	if (str == NULL)
		return (NULL);
	if (n == 0)
	{
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str[length] = '\0';
	while (length > 0)
	{
		str[length - 1] = (n % 10) * sign + 48;
		n = n / 10;
		length--;
	}
	if (sign < 0)
		str[length] = '-';
	return (str);
}
