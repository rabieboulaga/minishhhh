/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_help1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 23:44:29 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/11 23:44:57 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_execute(t_input *input)
{
	if (!input)
		return (8000);
	else
		check_heredoc(input);
	if (input->redirections)
	{
		redi_in(input);
	}
	else if (input->tok == AND)
		exec_and(input);
	else if (input->tok == OR)
		exec_or(input);
	else if (input->tok == PIPE)
		single_pipe(input);
	else if (input->tok == STR)
		return (exec_str(input));
	return (0);
}

void	exec_and(t_input *input)
{
	ft_execute(input->left);
	if (g_global.exited == 0)
		ft_execute(input->right);
}

void	exec_or(t_input *input)
{
	ft_execute(input->left);
	if (g_global.exited != 0)
		ft_execute(input->right);
}

void	fill_between_quote_1(char **str, char *s, int *i)
{
	while (s[*i])
	{
		*(*str)++ = s[(*i)++];
		if (s[*i] == 39)
		{
			*(*str)++ = s[(*i)++];
			*(*str) = '\0';
			return ;
		}
	}
}

int	exec_str(t_input *input)
{
	input->cmd = parsing_cmd(input->command);
	if (!input->cmd)
	{
		return (8000);
	}
	if (input->cmd && !input->cmd[0])
		(input->cmd = NULL);
	if (input->redirections != NULL)
	{
		if (input->redirections->fd != -1)
		{
			dup2(input->redirections->fd, STDIN_FILENO);
			close(input->redirections->fd);
			builtins(input->cmd);
			close(input->redirections->fd);
			return (8000);
		}
	}
	return (builtins(input->cmd));
}
