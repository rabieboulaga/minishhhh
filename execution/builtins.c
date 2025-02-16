/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:24:54 by rabie             #+#    #+#             */
/*   Updated: 2025/01/11 22:30:25 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	builtins(char **cmd)
{
	handle_signals(IN_PARENT);
	if (cmd == NULL)
		return (ft_exited(0, 0));
	if (ft_ncmp("echo", cmd[0], 4) == 0 && ft_strlen(cmd[0]) == 4)
		echo(cmd);
	else if (ft_ncmp("pwd", cmd[0], 3) == 0 && ft_strlen(cmd[0]) == 3)
		pwd();
	else if (ft_ncmp("cd", cmd[0], 2) == 0 && ft_strlen(cmd[0]) == 2)
		cd(cmd);
	else if (ft_ncmp("env", cmd[0], 3) == 0 && ft_strlen(cmd[0]) == 3)
		env(cmd);
	else if (ft_ncmp("unset", cmd[0], 5) == 0 && ft_strlen(cmd[0]) == 5)
		unset(cmd);
	else if (ft_ncmp("export", cmd[0], 6) == 0 && ft_strlen(cmd[0]) == 6)
		export(cmd);
	else if (ft_ncmp("exit", cmd[0], 4) == 0 && ft_strlen(cmd[0]) == 4)
		ft_exit(cmd);
	else
		return (cmd_execution(cmd));
	return (0);
}
