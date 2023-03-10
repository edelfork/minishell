/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 15:06:02 by gimartin          #+#    #+#             */
/*   Updated: 2023/02/27 11:18:11 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_input_line(t_command *cmd, char *tmp)
{
	char	*tmp2;

	tmp2 = NULL;
	malloc_c(&tmp2, ft_strlen(cmd->input_line) + 1);
	ft_strlcpy(tmp2, cmd->input_line, ft_strlen(cmd->input_line) + 1);
	free(cmd->input_line);
	malloc_c(&cmd->input_line, ft_strlen(tmp2) + ft_strlen(tmp) + 3);
	ft_strlcpy(cmd->input_line, tmp2, ft_strlen(tmp2) + 1);
	ft_strlcat(cmd->input_line, tmp,
		ft_strlen(tmp) + ft_strlen(tmp2) + 2);
	ft_strlcat(cmd->input_line, "\n", ft_strlen(cmd->input_line) + 2);
	free(tmp2);
}

void	get_right_var(char *key, char *ret, t_terminfo *terminfo)
{
	if (ft_getenv(key, terminfo))
		ft_strlcat(ret, ft_getenv(key, terminfo),
			ft_strlen(ret) + ft_strlen(ft_getenv(key, terminfo)) + 1);
	else if (!ft_strncmp(key, "?\0", 2))
	{
		free(key);
		key = ft_itoa(terminfo->last_exit);
		ft_strlcat(ret, key,
			ft_strlen(ret) + ft_strlen(key) + 1);
	}
	else if (!ft_strncmp(key, "$\0", 2))
		ft_strlcat(ret, "can't use getpid()!",
			ft_strlen(ret) + 21);
}

char	*try_expand_str(t_command *cmd, t_terminfo *terminfo)
{
	char	*ret;
	char	*key;
	int		i;

	i = 0;
	key = take_key(cmd->input_line);
	if (!key)
		return (cmd->input_line);
	malloc_c(&ret, ft_strlen_rl(cmd->input_line)
		- ft_strlen(key) + ft_strlen(ft_getenv(key, terminfo)));
	while (cmd->input_line[i] != '$')
		i++;
	ft_strlcpy(ret, cmd->input_line, i + 1);
	get_right_var(key, ret, terminfo);
	ft_strlcat(ret, &cmd->input_line[i + ft_strlen(key) + 1],
		ft_strlen(ret) + ft_strlen_rl(&cmd->input_line
		[i + ft_strlen(key) + 1]) + 1);
	free(cmd->input_line);
	if (key)
		free(key);
	return (ret);
}

int	heredoc_loop(char *tmp, char *d, t_command *cmd, t_terminfo *terminfo)
{
	int	i;

	i = 0;
	while (tmp && ft_strncmp(tmp, d, ft_strlen(d)) && g_child != -1)
	{
		if (cmd->input_line)
			join_input_line(cmd, tmp);
		else
		{
			malloc_c(&cmd->input_line, ft_strlen_rl(tmp) + 1);
			ft_strlcpy(cmd->input_line, tmp, ft_strlen_rl(tmp) + 1);
			ft_strlcat(cmd->input_line, "\n", ft_strlen(cmd->input_line) + 2);
		}
		free(tmp);
		tmp = NULL;
		if (cmd->to_exp)
			cmd->input_line = try_expand_str(cmd, terminfo);
		i++;
		tmp = readline("> ");
		if (g_child == -1)
			break ;
	}
	free(tmp);
	return (i);
}

void	take_heredoc_input(char *tmp, char *d,
	t_command *cmd, t_terminfo *terminfo)
{
	int	i;

	if (terminfo->last_exit == 130)
		terminfo->last_exit = 0;
	tmp = readline("> ");
	i = heredoc_loop(tmp, d, cmd, terminfo);
	end_take(tmp, i, d, terminfo);
}
