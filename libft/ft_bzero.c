/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:30:36 by epolkhov          #+#    #+#             */
/*   Updated: 2023/11/15 10:35:49 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*The  bzero() function writes lenzero bytes to the string s.  If	len is
       zero, bzero() does nothing.*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (n > 0)
	{
		*str = 0;
		str++;
		n--;
	}
}
