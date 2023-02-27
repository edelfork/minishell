/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:03:21 by gimartin          #+#    #+#             */
/*   Updated: 2023/02/27 11:18:11 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(t_command *cmd, t_terminfo *terminfo)
{
	int		i;

	i = 1;
	if (cmd->to_pipe)
		define_pipe(cmd);
	if (cmd->to_pipe_to)
		define_pipe_to(cmd);
	while (cmd->args[i] && !ft_strncmp("-n", cmd->args[i], 2))
		i++;
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i++], STDOUT_FILENO);
		if (cmd->args[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (ft_strncmp("-n", cmd->args[1], 2))
		ft_putchar_fd('\n', STDOUT_FILENO);
	terminfo->last_exit = 0;
}
