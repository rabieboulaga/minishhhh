/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:04:20 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/04 22:46:24 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int  open_heredoc(s_input *input, s_redir *red)
{
    // char file[]  = "/tmp/fil";
    char *str;
    int status;
    int fd;
    fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    // pid_t s = fork();
    
            // printf("ssssssssss\n");
    // if (s = 0)
    // {    
        while (1)
        {
            str = readline(">>");
            
            if (ft_strlen(str) == ft_strlen(input->redirections->file) && !ft_strncmp(str, input->redirections->file, ft_strlen(str)))
                break;
            ft_putstr_fd(str, fd);
            ft_putstr_fd("\n", fd);
        }
    
    // printf("before %s\n", input->redirections->file);
    
    // }
    // else
    // {
    //     // while (wait(NULL)) ;
    //     waitpid(s, &status, 0);
    // }
    // printf("line %d\n", fd);
    input->redirections->fd = dup(fd);
    // printf("line %d\n", input->redirections->fd);
    close(fd);
    return 0;
}
int     check_heredoc(s_input *input)
{
    s_redir *tmp;

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
            open_heredoc(input, tmp);
        }
        tmp = tmp->right;
    }
    // printf("line33 %p\n", input->redirections);    
    return 0;
}