/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_fields.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:04:34 by gimartin          #+#    #+#             */
/*   Updated: 2023/02/27 11:16:38 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len(char *s, char c)
{
	int	i;

	i = 0;
	if (!ft_strncmp(s, ">>", 2) || !ft_strncmp(s, "<<", 2))
		return (2);
	if (s[i] == '|' || s[i] == '>' || s[i] == '<')
		return (1);
	while (s[i])
	{
		if (s[i] == c && !is_open(s, i))
			return (i);
		if ((s[i] == '|' || s[i] == '>' || s[i] == '<') && !is_open(s, i))
			return (i);
		i++;
	}
	return (i);
}

int	find_start(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] == c && !is_open(s, i))
		i++;
	return (i);
}

int	sup_find_next(char *s, char c, int i)
{
	while (s[i])
	{
		if (s[i] == c && !is_open(s, i))
			break ;
		if ((s[i] == '|' || s[i] == '>' || s[i] == '<') && !is_open(s, i))
			break ;
		i++;
	}
	i += find_start(&s[i], c);
	return (i);
}

int	find_next_start(char *s, char c)
{
	int	i;

	i = 0;
	if (!ft_strncmp(s, ">>", 2) || !ft_strncmp(s, "<<", 2))
	{
		i += 2;
		while (!ft_isalnum(s[i]))
			i++;
		return (i);
	}
	if (s[i] == '|' || s[i] == '>' || s[i] == '<')
	{
		i++;
		while (!ft_isalnum(s[i]))
			i++;
		return (i);
	}
	return (sup_find_next(s, c, i));
}
