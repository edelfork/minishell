/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 15:27:13 by gimartin          #+#    #+#             */
/*   Updated: 2023/02/27 11:18:11 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ret;

	i = ft_strlen(s1);
	ret = malloc(sizeof(char) * i + 1);
	if (!ret || !s1)
		return (NULL);
	i = 0;
	while (*(s1 + i) != '\0')
	{
		*(ret + i) = *(s1 + i);
		i++;
	}
	*(ret + i) = '\0';
	return (ret);
}
