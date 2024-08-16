/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:23:27 by epolkhov          #+#    #+#             */
/*   Updated: 2023/11/15 16:36:37 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 *  The memset() function writes len bytes of value c (converted to an
     unsigned char) to the string b.
 * 	The memset() function returns its first argument.
 */

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned char	input;

	str = (unsigned char *)b;
	input = (unsigned char)c;
	while (len > 0)
	{
		*str = input;
		str++;
		len--;
	}
	return (b);
}
