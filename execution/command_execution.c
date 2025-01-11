/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:39:32 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/11 06:00:05 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	path_check(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[0] == 0)
		return (0);
	else if (str[0] == '.' && str[1] == '/')
		return (1);
	else if (str[0] == '.' && str[1] == '.' && str[2] == '/')
		return (1);
	else if (str[i - 1] == '/')
		return (1);
	return (0);
}

int	help(char **cmd)
{
	char	**test;
	char	*tmp;
	int		i;

	tmp = global.path;
	i = 0;
	while (*tmp != '=')
		tmp++;
	tmp++;
	if (*tmp)
	{
		test = ft_split(tmp, ':');
		while (test[i])
		{
			tmp = ft_strjoin(test[i], "/");
			global.path = ft_strjoin(tmp, cmd[0]);
			if (access(global.path, X_OK) == 0)
				return (1);
			i++;
		}
	}
	return (global.wall = 1, 0);
}

int	find_path(char **cmd)
{
	int	i;

	i = 0;
	while (global.env_copy[i])
	{
		if (ft_ncmp("PATH", global.env_copy[i], 4) == 0
			&& global.env_copy[i][4] == '=')
		{
			global.path = ft_strdup(global.env_copy[i]);
			if (help(cmd))
				return (1);
		}
		i++;
	}
	return (0);
}

int	cmd_execution(char **cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (0);
	if (pid == 0)
	{
		handle_signals(IN_CHILD);
		if (path_check(cmd[0]) && !chdir(cmd[0]))
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(" is a directory \n", 2);
			exit(126);
		}
		else if (find_path(cmd) && !path_check(cmd[0]))
		{
			execve(global.path, cmd, global.env_copy);
		}
		else if (path_check(cmd[0]) && access(cmd[0], F_OK) == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(127);
		}
		if (path_check(cmd[0]) && access(cmd[0], F_OK) == 0) //./minishell
		{
			if (access(cmd[0], X_OK) == -1)
			{
				ft_putstr_fd("Minishell: ", 2);
				ft_putstr_fd(cmd[0], 2);
				ft_putstr_fd(" Permission denied \n", 2);
				exit(126);
			}
			execve(cmd[0], cmd, global.env_copy);
			exit(0);
		}
		else
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			global.exited = 127;
			exit(127);
			// return (ft_exited(0, 127));
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		// global.exited = WEXITSTATUS(status);
		global.exited = (((status)&0xff00) >> 8);
	}
	return (global.exited);
}
