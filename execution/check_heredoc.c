/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:08:37 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/11 23:32:44 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// var_g = 0;

int	error_print(char *str, char *file, int fd)
{
	char	*expand_str;

	if (!str)
	{
		printf("minishell: warning: here-document delimited by end-of-file");
		printf(" (wanted `%s')\n", file);
		close(fd);
		exit(0);
	}
	if (str)
		expand_str = check_expand_herdoc(str);
	if (ft_strlen(str) == ft_strlen(file) && !ft_strncmp(str, file,
			ft_strlen(str)))
	{
		close(fd);
		exit(0);
	}
	ft_putstr_fd(expand_str, fd);
	ft_putstr_fd("\n", fd);
	return (0);
}

int	open_heredoc(t_redir *tmp)
{
	char	*str;
	int		fd;
	int		pid;
	int		status;

	pid = fork();
	fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	g_global.in_herdoc = 1;
	if (pid == 0)
	{
		while (1)
		{
			handle_signals(IN_HEREDOC);
			str = readline("> ");
			error_print(str, tmp->file, fd);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		tmp->fd = open("example.txt", O_RDONLY, 0644);
		close(fd);
	}
	g_global.in_herdoc = 0;
	return (0);
}

int	check_heredoc(t_input *input)
{
	t_redir	*tmp;

	tmp = input->redirections;
	if (input->tok == PIPE)
	{
		check_heredoc(input->left);
		check_heredoc(input->right);
	}
	while (tmp != NULL)
	{
		if (tmp->tok == HEREDOC)
		{
			open_heredoc(tmp);
		}
		tmp = tmp->right;
	}
	return (0);
}
