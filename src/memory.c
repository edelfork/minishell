/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:08:51 by gimartin          #+#    #+#             */
/*   Updated: 2023/02/27 11:18:11 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dict(t_dict *env)
{
	t_dict	*tmp;
	t_dict	*tmp2;

	tmp = env;
	while (tmp)
	{
		tmp2 = tmp;
		if (tmp2->key)
			free(tmp2->key);
		else
			break ;
		if (tmp2->value)
			free(tmp2->value);
		tmp = tmp->next;
		free(tmp2);
	}
}

void	malloc_c(char **dst, int len)
{
	*dst = malloc(sizeof(char) * len);
	if (!*dst)
		die("Malloc error");
}

void	malloc_c_ptr(char ***dst, int len)
{
	*dst = malloc(sizeof(char *) * len);
	if (!*dst)
		die("Malloc error");
}

void	malloc_and_check_dict(t_dict **dst, int len)
{
	*dst = malloc(sizeof(t_dict) * len);
	if (!*dst)
		die("Malloc error");
	dst[0]->key = NULL;
	dst[0]->value = NULL;
	dst[0]->next = NULL;
}
