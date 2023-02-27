/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:13:07 by gimartin          #+#    #+#             */
/*   Updated: 2023/02/27 11:18:11 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	i2;

	i = 0;
	if (*needle == 0 || needle == NULL)
		return ((char *)haystack);
	while (haystack[i] != '\0' && i < len)
	{
		i2 = 0;
		while (needle[i2] == haystack[i + i2] && i + i2 < len)
		{
			if (needle[i2 + 1] == '\0')
				return ((char *)haystack + i);
			i2++;
		}
		i++;
	}
	return (NULL);
}
