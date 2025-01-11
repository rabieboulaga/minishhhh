/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:42:59 by rabia             #+#    #+#             */
/*   Updated: 2025/01/11 01:35:39 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int     env(char **cmd)
{
    int i;
    // int j = 0;
    // while (global->env_copy[j])
    //     j++;
    // printf("%d\n\n", j);
    
    i = 0;
    if (cmd[1])
    {
        printf("env: ‘%s’: No such file or directory\n", cmd[1]);
        global.exited = 88;
        return (ft_exited(1, 127));
    }
    while (global.env_copy[i])
    {
        if (ft_strchr(global.env_copy[i], '=') != NULL)
            printf("%s\n", global.env_copy[i]);
        i++;
    }
    return (ft_exited(1, 0));
}
// ‘%s’ check if there is any problem