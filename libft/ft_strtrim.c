/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aheinane <aheinane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:14:36 by epolkhov          #+#    #+#             */
/*   Updated: 2024/06/12 13:01:29 by aheinane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/***
 * Allocates (with malloc(3)) and returns a copy of
 ’s1’ with the characters specified in ’set’ removed
 from the beginning and the end of the string.
 */

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start_position;
	char	*end_position;
	char	*trim_str;
	size_t	trim_len;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	len = ft_strlen(s1);
	start_position = (char *)s1;
	end_position = start_position + len - 1;
	while (*start_position && ft_strchr(set, *start_position))
		start_position++;
	if (*start_position == '\0')
		return (ft_strdup(""));
	while (end_position > start_position && ft_strchr(set, *end_position))
		end_position--;
	trim_len = end_position - start_position + 1;
	trim_str = (char *)malloc(trim_len + 1);
	if (trim_str == NULL)
		return (NULL);
	ft_strlcpy(trim_str, start_position, trim_len + 1);
	return (trim_str);
}
