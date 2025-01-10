/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 23:08:37 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/10 22:38:02 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"
// var_g = 0;
void  ft_SIGINT_(int pid)
{
    (void)pid;
    
	write(1, "\n", 1);
	close(STDIN_FILENO);
	global.status = 130;
	exit(130);
}

int  open_heredoc(s_redir *tmp)
{
    char *str;
    int fd;
    char *expand_str;
    int pid;
    int status;
    pid = fork();
    fd = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if (pid == 0)
    {
        while (1)
        {
            global.in_herdoc = 1;
            // signal(SIGINT, ft_SIGINT_);
            handle_signals(IN_HEREDOC);
            str = readline(">>");
            // handle signal parent
            if (!str)
            {
                printf("minishell: warning: here-document at line 10 delimited by end-of-file");
                printf(" (wanted `%s')\n", tmp->file);
                close (fd);
                exit(0);
            }
            if(str)
                expand_str = check_expand_herdoc(str);
            if (ft_strlen(str) == ft_strlen(tmp->file) && !ft_strncmp(str, tmp->file, ft_strlen(str)))
            {
                close (fd);
                exit(0);
            }
            ft_putstr_fd(expand_str, fd);
            ft_putstr_fd("\n", fd);
            // if (str)
            // {
            //     free(str);
            //     free(expand_str);
            // }
        }    
    }
    else
    {
        waitpid(pid, &status, 0);
        global.in_herdoc = 0;
        tmp->fd = open("example.txt", O_RDONLY, 0644);
        close(fd);
    }
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
            open_heredoc(tmp);             
        }
        tmp = tmp->right;
    }
    // printf("line33 %p\n", input->redirections);    
    return 0;
}