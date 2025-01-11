/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:52:34 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/11 22:59:54 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// int     redi_in(s_input *input)
// {
//     int fd;
//     int fd0;

//     while (input->redirections->right != NULL)
//     {
//         fd = open(input->redirections->file, O_RDONLY);
//         if (fd == -1)
//         {
//             ft_putstr_fd("Minishell: ", 2);
//             return (perror(input->redirections->file), 0);
//         }
//         input->redirections = input->redirections->right;
//     }
//     fd = open(input->redirections->file, O_RDONLY);
//     if (fd == -1)
//     {
//         ft_putstr_fd("Minishell: ", 2);
//         return (perror(input->redirections->file), 0);
//     }
//     fd0 = dup(STDIN_FILENO);        //save current stdin
//     dup2(fd, STDIN_FILENO);          //redirect stdin to the file
//     close(fd);                      // close the file descriptor of the file
//     exec_str(input);                // execute the cmd
//     dup2(fd0, STDIN_FILENO);         //restore original stdin
//     close(fd0);                      //close the saved stdin descriptor
//     return (1);
// }

int	do_direct(int fd, int dest)
{
	if (dup2(fd, dest) == -1)
	{
		if (fd != dest)
			close(fd);
		return (perror("dup2"), 1);
	}
	if (fd != dest)
		close(fd);
	return (EXIT_SUCCESS);
}

int	redi_in(s_input *input)
{
	int	fd0;
	int	fd1;

	fd1 = dup(STDOUT_FILENO);
	fd0 = dup(STDIN_FILENO);
	if (in_out_files(input))
		exec_str(input);
	dup2(fd0, STDIN_FILENO);
	dup2(fd1, STDOUT_FILENO);
	close(fd0);
	close(fd1);
	return (1);
}

int	in_out_files(s_input *input)
{
	s_redir	*tmp;

	tmp = input->redirections;
	while (tmp != NULL)
	{
		if (red_utils1_in(tmp) == 0)
			return (0);
		else if (red_utils2_out(tmp) == 0)
			return (0);
		else if (red_utils3_append(tmp) == 0)
			return (0);
		tmp = tmp->right;
	}
	return (1);
}
