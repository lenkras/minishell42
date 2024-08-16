/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epolkhov <epolkhov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:48:37 by epolkhov          #+#    #+#             */
/*   Updated: 2023/11/15 14:35:36 by epolkhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * The strrchr() function is identical to strchr(), except it locates the
     last occurrence of c.
	The functions strrchr() return a pointer to the located
     character, or NULL if the character does not appear in the string.
 */

char	*ft_strrchr(const char *s, int c)
{
	char	*last_showed;
	int		i;

	i = 0;
	last_showed = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			last_showed = ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0' && s[i] == '\0')
		return ((char *)&s[i]);
	return (last_showed);
}
