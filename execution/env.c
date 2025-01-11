/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:42:59 by rabia             #+#    #+#             */
/*   Updated: 2025/01/11 23:32:44 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	env(char **cmd)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		printf("env: ‘%s’: No such file or directory\n", cmd[1]);
		g_global.exited = 88;
		return (ft_exited(1, 127));
	}
	while (g_global.env_copy[i])
	{
		if (ft_strchr(g_global.env_copy[i], '=') != NULL)
			printf("%s\n", g_global.env_copy[i]);
		i++;
	}
	return (ft_exited(1, 0));
}
// ‘%s’ check if there is any problem