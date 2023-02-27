/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:04:52 by gimartin          #+#    #+#             */
/*   Updated: 2023/02/27 11:18:11 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_heredoc(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strncmp(&line[i], "<<", 2))
			return (1);
		i++;
	}
	return (0);
}

int	is_redir(char *line)
{
	if (!ft_strncmp(line, "<<\0", 3))
		return (3);
	else if (!ft_strncmp(line, ">>\0", 3))
		return (2);
	else if (!ft_strncmp(line, ">\0", 2))
		return (1);
	else if (!ft_strncmp(line, "<\0", 2))
		return (0);
	return (-1);
}

int	quoted(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '=')
		i++;
	i++;
	if (line[i] == '\'' || line[i] == '"')
		return (1);
	return (0);
}

int	is_token(char *line)
{
	if (ft_strncmp(line, "<\0", 2) && ft_strncmp(line, "<<\0", 3) \
		&& ft_strncmp(line, ">\0", 2) && ft_strncmp(line, ">>\0", 3) \
		&& ft_strncmp(line, "|\0", 2))
		return (0);
	return (1);
}

int	is_token_char(char c)
{
	if (c == '|')
		return (1);
	return (0);
}
