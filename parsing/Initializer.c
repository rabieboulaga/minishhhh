/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:21:38 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 23:33:07 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	save_input_output(int *fd_input, int *fd_output)
{
	*fd_input = dup(0);
	*fd_output = dup(1);
	close(*fd_input);
	close(*fd_output);
}

int	find_char(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			return (i);
		s++;
		i++;
	}
	return (-1);
}

void	ft_initialize_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	g_global.env_copy = ft_malloc((i + 1) * sizeof(char *));
	if (!g_global.env_copy)
		return ;
	i = 0;
	while (env[i])
	{
		g_global.env_copy[i] = ft_strdup(env[i]);
		i++;
	}
	g_global.env_copy[i] = NULL;
}

void	ft_initialize(char **env, int *fd_input, int *fd_output)
{
	g_global.executed = 0;
	g_global.exited = 0;
	g_global.in_herdoc = 0;
	g_global.test = 0;
	save_input_output(fd_input, fd_output);
	if (g_global.exited == 0)
		ft_initialize_env(env);
}
