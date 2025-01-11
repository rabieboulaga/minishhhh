/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:52:34 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/11 19:22:23 by rboulaga         ###   ########.fr       */
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

int     redi_in(s_input *input)
{
    int fd0;
    int fd1;

    fd1 = dup(STDOUT_FILENO);
    fd0 = dup(STDIN_FILENO); 
    if (in_out_files(input))        //save current stdin
        exec_str(input);                // execute the cmd 
    dup2(fd0, STDIN_FILENO);         //restore original stdin 
    dup2(fd1, STDOUT_FILENO);
    close(fd0);
    close(fd1);                      //close the saved stdin descriptor 
    return (1);
}

static int    do_direct(int fd, int dest)
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
int     in_out_files(s_input *input)
{
    int fd;
    s_redir *tmp;

    tmp = input->redirections;
    while (tmp != NULL)
    {
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
        else if(tmp->tok == OUT)
        {
            fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC , 0666);
            
            if (fd == -1)
            {
                ft_putstr_fd("Minishell: ", 2);
                return(perror(tmp->file), 0);
            }
            do_direct(fd, STDOUT_FILENO);
        }
        else if(tmp->tok == APPEND)
        {
            fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND , 0666);
            if (fd == -1)
            {
                ft_putstr_fd("Minishell: ", 2);
                return (perror(tmp->file), 0);
            }
            do_direct(fd, STDOUT_FILENO);
        } 
        tmp = tmp->right;
    }
    return (1);
}

    // check_in(input);

int     redirections(s_input *input)
{
    if (input->redirections->tok == 0)
        in_out_files(input);
    
    return 1;
}