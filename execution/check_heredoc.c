/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:08:37 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/06 00:33:12 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int  open_heredoc(s_input *input, s_redir *tmp)
{
    char *str;
    int status;
    int fd;
    fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    while (1)
    {
        str = readline(">>");
        
        if (ft_strlen(str) == ft_strlen(tmp->file) && !ft_strncmp(str, tmp->file, ft_strlen(str)))
            break;
        ft_putstr_fd(str, fd);
        ft_putstr_fd("\n", fd);
    }
    // printf("before %d\n", tmp->fd);    
    tmp->fd = open("example.txt", O_RDONLY, 0644);
    // printf("after %d\n", tmp->fd);    
    
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