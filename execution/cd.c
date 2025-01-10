/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:04:06 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/10 00:12:19 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"





void    pwd_update()
{
    int i;
    char buff[PATH_MAX];

    i = 0;
    while(global.env_copy[i] && ft_ncmp(global.env_copy[i], "OLDPWD", 6))
    {    
        i++;
    }
    // free(global.env_copy[i]);    
    getcwd(buff, sizeof(buff));
    global.env_copy[i] = ft_strjoin("OLDPWD=", buff);
}
int ft_exited(int d, int exit)
{
    global.exited = exit;
    return (d);
}

int arg_numbers(char **cmd)
{
    int i = 0;

    while (cmd[i])
        i++;
    if (i > 2)
    {
        ft_putstr_fd("minishell: cd: too many arguments\n", 2);
        return 1;
    }
    return 0;
} 

int		cd(char **cmd)
{
    char *tmp;
    
    if(arg_numbers(cmd))
        return(ft_exited(1, 1)); 
    else if (!cmd[1])
    {
        tmp = getenv("HOME");
        if (tmp)
        {
            pwd_update();   
            chdir(tmp);
        }
    }
    else if (cmd[1])
    {
        pwd_update();   
        if (chdir(cmd[1]) == 0)
            return(ft_exited(0, 0));
        ft_putstr_fd("minishell: cd: ", 2);
        ft_putstr_fd(cmd[1], 2);
        ft_putstr_fd(": No such file or directory\n", 2);
        return(ft_exited(1, 1));
    }
    return(ft_exited(0, 0)); 
}
