/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 19:32:23 by epolkhov          #+#    #+#             */
/*   Updated: 2023/11/15 12:11:39 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The memchr() function scans the initial n bytes of the memory
       area pointed to by s for the first instance of c.  Both c and the
       bytes of the memory area pointed to by s are interpreted as
       unsigned char.
	function return a pointer to the
       matching byte or NULL if the character does not occur in the
       given memory area.
 */

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		input;
	size_t				i;

	str = (const unsigned char *)s;
	input = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == input)
			return ((void *)&str[i]);
		i++;
	}
	return (NULL);
}
