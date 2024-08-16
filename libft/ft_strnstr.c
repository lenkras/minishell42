/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:15:57 by epolkhov          #+#    #+#             */
/*   Updated: 2023/11/15 17:56:49 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The strnstr() function locates the first occurrence of the null-termi-
     nated string needle in the string haystack, where not more than len char-
     acters are searched.  Characters that appear after a `\0' character are
     not searched.
 * If needle is an empty string, haystack is returned; if needle occurs
     nowhere in haystack, NULL is returned; otherwise a pointer to the first
     character of the first occurrence of needle is returned.
 */

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	if (!haystack && !n)
		return (NULL);
	if (*needle == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] && n > i)
	{
		j = 0;
		while (haystack[i + j] && needle[j] && \
		haystack[i + j] == needle[j] && n > i + j)
			j++;
		if (!needle[j])
			return ((char *)&haystack[i]);
		if (!haystack[i + j] || i + j == n)
			return (NULL);
		i++;
	}
	return (NULL);
}
/**
 * 1. checks if the current portion of the haystack matches the needle
 * 2. checks if the entire needle has been found 
 	(i.e., the inner loop completed successfully). needle exists in
	 the current portion of the haystack, and the function returns the
	  position where it starts in the haystack.
 * 3. checks if we've reached the end of the haystack or if the limit
  specified by n has been reached. If true, it means we should stop searching,
   and the function returns NULL
 */