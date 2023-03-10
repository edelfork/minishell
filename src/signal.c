/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:04:37 by gimartin          #+#    #+#             */
/*   Updated: 2023/02/27 11:16:38 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern void	rl_replace_line(const char *str, int n);

void	heredoc_sigint(void)
{
	ft_putstr_fd("^C", STDOUT_FILENO);
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	g_child = -1;
}

void	sigint(void)
{
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", STDIN_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

void	parent_signals(int sig)
{
	if (sig == SIGINT)
		sigint();
}

void	parent_signals_heredoc(int sig)
{
	if (sig == SIGINT)
		heredoc_sigint();
}

void	child_signals(int sig)
{
	if (sig == SIGINT)
	{
		kill(g_child, SIGINT);
		ft_putendl_fd("^C", STDOUT_FILENO);
	}
	else if (sig == SIGQUIT)
	{
		kill(g_child, SIGINT);
		ft_putendl_fd("^\\Quit: 3", STDOUT_FILENO);
		g_child = -1;
	}
}
