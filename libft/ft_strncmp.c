/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:11:18 by epolkhov          #+#    #+#             */
/*   Updated: 2023/11/15 14:04:23 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * strncmp()  functions	 lexicographically compare the
       null-terminated strings s1 and s2.
The strncmp() function compares not more than n characters.   Because
       strncmp()  is  designed	for comparing strings rather than binary data,
       characters that appear after a `\0' character are not compared.
The strcmp() and	strncmp() functions return an  integer	greater	 than,
       equal  to,  or less than	0, according as	the string s1 is greater than,
       equal to, or less than the string s2.  The comparison is	done using un-
       signed characters, so that `\200' is greater than `\0'.
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while ((str1[i] || str2[i]) && (i < n))
	{
		if ((str1[i] < str2[i]) || (str1[i] > str2[i]))
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
