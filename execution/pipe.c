/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 16:47:51 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/11 05:48:03 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int pipe_left(int *pipefd, s_input *input)
{
    int status;
    
    close(pipefd[0]);                       
    dup2(pipefd[1], STDOUT_FILENO);       
    close(pipefd[1]);                      
    if (input->left->tok == PIPE)
        single_pipe(input->left);    
    if (input->left->command)
    {
        if(in_out_files(input->left))
            status = exec_str(input->left);
        else
            return (1); 
    }
    return (status);
}

int     single_pipe(s_input *input)
{
    int status;    
    int pipefd[2];

    pipe(pipefd);
    pid_t left = fork();
    if (left == 0)
        (handle_signals(IN_CHILD), exit(pipe_left(pipefd, input)));
    pid_t right = fork();
    if (right == 0)
    {
        handle_signals(IN_CHILD);
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        if(in_out_files(input->right))
            status = exec_str(input->right);
        else    
            exit(1);  
        exit(status);
    }
    close(pipefd[1]);
    close(pipefd[0]);
    (waitpid(left, &status, 0), waitpid(right, &status, 0));
    global.exited = (((status) & 0xff00) >> 8);   
    return 0;
}

// int     exe(char **cmd ,s_input *input)
// {
    
//     if (input->tok == PIPE)
//         single_pipe(input);
//     else if (input->tok == STR)
//         builtins(cmd);
//     // else if (input->tok == IN || input->tok == OUT)
//     // {    
//     //     redirections(input, global);    
//     //     printf(">dsfsdfsdfsdfsd\n");
//     // }
//     return 0;
// }
  
    //-->>>> explanation of tree <<<<-
    // if (input->tok == PIPE)
    //     printf("this is pipe\n");
    // printf("this is right->second command = %s\n", input->right->command);
    // input = input->left;
    // if (input->tok == PIPE)
    //     printf("this is pipe\n");
    // printf("this is left->first command = %s\n", input->left->command);
    // printf("this is right->second command = %s\n", input->right->command);
    

//left fork
    // close(pipefd[0]);                       
        // dup2(pipefd[1], STDOUT_FILENO);       
        // close(pipefd[1]);                      
        // if (input->left->tok == PIPE)
            // single_pipe(input->left);    
        // if (input->left->command)
        // {
            // if(in_out_files(input->left))
                // status = exec_str(input->left);
            // else
                // exit(1); 
        // }

// from PIP 
        // handle_signals(IN_CHILD);
        // exit(pipe_left(pipefd, input));


// from waitpid 
    // waitpid(left, &status, 0);
    // waitpid(right, &status, 0);