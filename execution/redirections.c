/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:52:34 by rboulaga          #+#    #+#             */
/*   Updated: 2024/12/27 07:14:03 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int     redi_in(s_input *input)
{
    int fd;
    int fd0;
 
    fd0 = dup(STDIN_FILENO);
    fd = open(input->redirections->file, O_RDONLY);
    dup2(fd, STDIN_FILENO);
    close(fd);
    exec_str(input);
    dup2(fd0, STDIN_FILENO);
    close(fd0);
    return (1);
}

int     redirections(s_input *input)
{
    if (input->redirections->tok == 0)
        redi_in(input);
    return 1;
}