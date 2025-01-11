/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:39:32 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/11 23:33:07 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	path_check(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[0] == 0)
		return (0);
	else if (str[0] == '/')
		return (1);
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

	tmp = g_global.path;
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
			g_global.path = ft_strjoin(tmp, cmd[0]);
			if (access(g_global.path, X_OK) == 0)
				return (1);
			i++;
		}
	}
	return (g_global.wall = 1, 0);
}

int	find_path(char **cmd)
{
	int	i;

	i = 0;
	while (g_global.env_copy[i])
	{
		if (ft_ncmp("PATH", g_global.env_copy[i], 4) == 0
			&& g_global.env_copy[i][4] == '=')
		{
			g_global.path = ft_strdup(g_global.env_copy[i]);
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
		utils1(cmd);
		utils2(cmd);
	}
	else
	{
		waitpid(pid, &status, 0);
		g_global.exited = (((status) & 0xff00) >> 8);
	}
	return (g_global.exited);
}
