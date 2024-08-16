/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 10:50:40 by epolkhov          #+#    #+#             */
/*   Updated: 2023/11/16 13:19:29 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The atoi() function converts the initial portion of the string pointed to
     by str to int representation.
 */

static int	convert_nb(const char *str, long nb, int sign)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		if (nb > LONG_MAX / 10)
		{
			if (sign < 0)
				return (0);
			return (-1);
		}
		nb = nb * 10;
		if (nb > LONG_MAX - (str[i] - 48))
		{
			if (sign < 0)
				return (0);
			return (-1);
		}
		nb = nb + (str[i] - 48);
		i++;
	}
	return (nb);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	long	nb;
	int		sign;

	nb = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign = sign * (-1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	nb = convert_nb(str + i, nb, sign);
	return ((int)nb * sign);
}
