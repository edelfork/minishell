/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gimartin <gimartin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 16:12:15 by gimartin          #+#    #+#             */
/*   Updated: 2023/02/27 11:16:38 by gimartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sup_sub_args(char **tmp, int j, char **helper, t_command *cmd)
{
	int	i2;
	int	i;

	i = j + 1;
	i2 = 0;
	while (tmp[i2])
	{
		malloc_c(&helper[j], ft_strlen(tmp[i2]) + 1);
		ft_strlcpy(helper[j++], tmp[i2], ft_strlen(tmp[i2]) + 1);
		i2++;
	}
	while (cmd->args[i])
	{
		malloc_c(&helper[j], ft_strlen(cmd->args[i]) + 1);
		ft_strlcpy(helper[j++], cmd->args[i], ft_strlen(cmd->args[i]) + 1);
		i++;
	}
	helper[j] = NULL;
	free_array_of_array(cmd->args);
	cmd->args = helper;
}

void	substitute_args(t_command *cmd, char **tmp)
{
	int		j;
	int		len;
	char	**helper;

	len = count_args(cmd->args) + count_args(tmp);
	malloc_c_ptr(&helper, len + 1);
	j = 0;
	while (cmd->args[j] && !has_wildcard(cmd->args[j]))
	{
		malloc_c(&helper[j], ft_strlen(cmd->args[j]) + 1);
		ft_strlcpy(helper[j], cmd->args[j], ft_strlen(cmd->args[j]) + 1);
		j++;
	}
	sup_sub_args(tmp, j, helper, cmd);
}

int	sup_guess(t_command *cmd, int i, int j, int k)
{
	if (!is_open(cmd->args[i], j)
		&& (cmd->args[i][j] == '*' || cmd->args[i][j] == '?'))
	{
		malloc_c(&cmd->portions[k], 2);
		ft_strlcpy(cmd->portions[k], &cmd->args[i][j], 2);
		k++;
	}
	else if (!is_open(cmd->args[i], j) && cmd->args[i][j] == '[')
	{
		if (take_brackets_param(&cmd->args[i][j], &cmd->portions[k]) == -1)
			helper_guess(cmd);
		k++;
		j += try_parse_brackets(&cmd->args[i][j]) - 1;
	}
	else
	{
		take_string_portion(&cmd->args[i][j], &cmd->portions[k]);
		j += ft_strlen(cmd->portions[k++]);
	}
	return (0);
}

int	free_guess(char **tmp, t_command *cmd)
{
	tmp = get_results(cmd->portions, count_results(cmd->portions));
	if (!tmp)
		return (-1);
	substitute_args(cmd, tmp);
	free_array_of_array(tmp);
	free_array_of_array(cmd->portions);
	cmd->portions = NULL;
	return (1);
}

int	free_hidden_guess(char **tmp, t_command *cmd)
{
	tmp = get_hidden_results(cmd->portions, count_h_results(cmd->portions));
	if (!tmp)
		return (-1);
	substitute_args(cmd, tmp);
	free_array_of_array(tmp);
	free_array_of_array(cmd->portions);
	cmd->portions = NULL;
	return (1);
}
