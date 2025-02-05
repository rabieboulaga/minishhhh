/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 20:58:03 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/11 23:32:44 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	utils2(char **cmd)
{
	if (path_check(cmd[0]) && access(cmd[0], F_OK) == 0)
	{
		if (access(cmd[0], X_OK) == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(" Permission denied \n", 2);
			free_garbage();
			exit(126);
		}
		execve(cmd[0], cmd, g_global.env_copy);
		exit(0);
	}
	else
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_garbage();
		exit(127);
	}
	return (0);
}

int	utils1(char **cmd)
{
	if (path_check(cmd[0]) && !chdir(cmd[0]))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(" is a directory \n", 2);
		free_garbage();
		exit(126);
	}
	else if (find_path(cmd) && !path_check(cmd[0]))
	{
		execve(g_global.path, cmd, g_global.env_copy);
		exit(0);
	}
	else if (path_check(cmd[0]) && access(cmd[0], F_OK) == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_garbage();
		exit(127);
	}
	return (0);
}
