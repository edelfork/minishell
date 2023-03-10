/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:10:50 by gimartin          #+#    #+#             */
/*   Updated: 2023/02/27 11:18:11 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	next_level(t_terminfo *terminfo)
{
	char	*bef;

	bef = ft_itoa((ft_atoi(ft_getenv("SHLVL", terminfo)) + 1));
	change_exist_var_in_dict("SHLVL", bef, terminfo->env);
	free_array_of_array(terminfo->glob_environ);
	transform_environ(terminfo);
	free(bef);
}

void	parent_behaviour(t_command *tmp, int status, t_terminfo *terminfo)
{
	if (terminfo->is_suspended && !tmp->delimiter
		&& !ft_strncmp("cat\0", &tmp->cmd[ft_strlen(tmp->cmd) - 3], 4)
		&& tmp->next != NULL && !tmp->args[1])
		return (treat_suspended_cat(tmp, terminfo));
	else if (!tmp->delimiter)
	{
		wait(&status);
		waitpid(g_child, &status, 0);
		if (!terminfo->signaled)
		{
			if (WIFEXITED(status))
				terminfo->last_exit = status / 256;
			else if (WIFSIGNALED(status))
				terminfo->last_exit = 128 + status;
			else
				terminfo->last_exit = status;
		}
		restore_fd(tmp);
		terminfo->is_suspended = 0;
	}
	else
		treat_heredoc_child(&status, tmp, terminfo);
}

void	maieutica(t_command *tmp, int status, t_terminfo *terminfo)
{
	g_child = fork();
	if (g_child == -1)
		die(strerror(errno));
	if (g_child == 0)
	{
		ft_memset(&terminfo->acts, 0, sizeof(terminfo->acts));
		if (ft_strlen(tmp->cmd) > 9
			&& !ft_strncmp(&tmp->cmd[ft_strlen(tmp->cmd) - 9], "minishell", 9))
			next_level(terminfo);
		execve(tmp->cmd, tmp->args, terminfo->glob_environ);
	}
	else
	{
		add_signals(terminfo, tmp);
		parent_behaviour(tmp, status, terminfo);
	}
}

void	define_input_redirection(char **tmp, t_command *cmd, t_terminfo *t)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (!ft_strncmp(tmp[i], "<\0", 2))
			define_input(tmp[++i], cmd, t);
		i++;
	}
}

void	define_output_redirection(char **tmp, t_command *cmd)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		if (!ft_strncmp(tmp[i], ">\0", 2))
			define_output(tmp[++i], cmd);
		if (!ft_strncmp(tmp[i], ">>\0", 3))
			define_append_output(tmp[++i], cmd);
		i++;
	}
}
