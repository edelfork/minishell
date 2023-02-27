/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:37:02 by gimartin          #+#    #+#             */
/*   Updated: 2023/02/27 11:18:11 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*ret;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	s1 = (unsigned char *) dst;
	s2 = (unsigned char *) src;
	ret = dst;
	i = 0;
	while (i < n)
	{
		*(s1 + i) = *(s2 + i);
		i++;
	}
	return (ret);
}
