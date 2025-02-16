/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 05:57:49 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/11 23:32:44 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	exit_arguments(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	return (0);
}

int	args_req(char **cmd, int *flag)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	*flag = i;
	if (i > 1)
	{
		i = 0;
		while (cmd[1][i])
		{
			if (ft_isalpha(cmd[1][i]))
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_exit(char **cmd)
{
	int	flag;

	flag = 0;
	if (args_req(cmd, &flag))
	{
		ft_putstr_fd("exit : ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_garbage();
		exit(2);
	}
	else if (exit_arguments(cmd))
		return (1);
	if (flag == 2)
	{
		g_global.exited = ft_atoi(cmd[1]);
		g_global.exited %= 256;
		free_garbage();
		exit(g_global.exited);
	}
	else
		return (free_garbage(), exit(g_global.exited), 0);
	return (0);
}
