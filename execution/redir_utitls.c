/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utitls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 23:38:27 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/11 22:58:55 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	red_utils1_in(t_redir *tmp)
{
	int	fd;

	if (tmp->tok == IN)
	{
		fd = open(tmp->file, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			return (perror(tmp->file), 0);
		}
		do_direct(fd, STDIN_FILENO);
	}
	return (1);
}

int	red_utils2_out(t_redir *tmp)
{
	int	fd;

	if (tmp->tok == OUT)
	{
		fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			return (perror(tmp->file), 0);
		}
		do_direct(fd, STDOUT_FILENO);
	}
	return (1);
}

int	red_utils3_append(t_redir *tmp)
{
	int	fd;

	if (tmp->tok == APPEND)
	{
		fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
		{
			ft_putstr_fd("Minishell: ", 2);
			return (perror(tmp->file), 0);
		}
		do_direct(fd, STDOUT_FILENO);
	}
	return (1);
}
