/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:03:23 by gimartin          #+#    #+#             */
/*   Updated: 2023/02/27 11:18:11 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *line, t_terminfo *terminfo)
{
	t_dict	*tmp;
	t_dict	*tmp2;

	if (terminfo->env)
	{
		tmp = terminfo->env;
		while (tmp)
		{
			if (!ft_strncmp(tmp->key, line, ft_strlen(line) + 1))
				return (tmp->value);
			tmp = tmp->next;
		}
	}
	if (terminfo->var && terminfo->var->key)
	{
		tmp2 = terminfo->var;
		while (tmp2)
		{
			if (!ft_strncmp(tmp2->key, line, ft_strlen(line) + 1))
				return (tmp2->value);
			tmp2 = tmp2->next;
		}
	}
	return (NULL);
}

void	env(t_command *cmd, t_terminfo *terminfo)
{
	t_dict	*tmp;

	if (cmd->to_pipe)
		define_pipe(cmd);
	if (cmd->to_pipe_to)
		define_pipe_to(cmd);
	tmp = terminfo->env;
	while (tmp)
	{
		if (tmp->key && tmp->value)
		{
			ft_putstr_fd(tmp->key, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(tmp->value, 1);
		}
		tmp = tmp->next;
	}
	terminfo->last_exit = 0;
}
