/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 15:52:34 by rboulaga          #+#    #+#             */
/*   Updated: 2024/12/29 03:36:32 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"


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
int     redi_in(s_input *input)
{
    int fd;
    int fd0;
    
    while (input->redirections->right != NULL)
    {
        fd = open(input->redirections->file, O_RDONLY);
        if (fd == -1)
        {
            ft_putstr_fd("Minishell: ", 2);
            return (perror(input->redirections->file), 0);
        }
        input->redirections = input->redirections->right;
    }
    fd = open(input->redirections->file, O_RDONLY);
    if (fd == -1)
    {            
        ft_putstr_fd("Minishell: ", 2);
        return (perror(input->redirections->file), 0);
    }
    fd0 = dup(STDIN_FILENO);        //save current stdin
    dup2(fd, STDIN_FILENO);          //redirect stdin to the file
    close(fd);                      // close the file descriptor of the file
    exec_str(input);                // execute the cmd
    dup2(fd0, STDIN_FILENO);         //restore original stdin 
    close(fd0);                      //close the saved stdin descriptor 
    return (1);
}

// int     in_out_files(s_input *input)
// {
//     int fd;
//     int fd0;
    
//     while (input->redirections->right != NULL)
//     {
//        if (input->redirections->tok == IN)
//        {
//             fd = open(input->redirections->file, O_RDONLY);
//             if (fd == -1)
//             {
//                 ft_putstr_fd("Minishell: ", 2);
//                 return (perror(input->redirections->file), 0);
//             }
//             do_direct(fd, STDIN_FILENO);
//        }
//        else if(input->redirections->tok == OUT)
//        {
//             fd = open(input->redirections->file, O_WRONLY | O_CREAT | O_TRUNC , 0666);
//             if (fd == -1)
//             {
//                 ft_putstr_fd("Minishell: ", 2);
//                 return (perror(input->redirections->file), 0);
//             }
//             do_direct(fd, STDOUT_FILENO);
//        } 
//         input->redirections = input->redirections->right;
//     }
//     return (1);
// }

    // check_in(input);

int     redirections(s_input *input)
{
    if (input->redirections->tok == 0)
        redi_in(input);
    
    return 1;
}