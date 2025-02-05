/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:27:09 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/11 23:33:07 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

// void    free_list(char **str)
// {
//     int i;

//     i = 0;
//     while (str[i])
//     {
//         free(str[i])
//         i++;
//     }
// }

void	copying_2(char *v)
{
	int		i;
	char	**tmp;

	i = 0;
	while (g_global.env_copy[i])
		i++;
	tmp = malloc((i + 2) * sizeof(char *));
	ft_lstadd_back_garbage(&(g_global.garbage), ft_lstnew_garbage(tmp));
	i = 0;
	while (g_global.env_copy[i])
	{
		tmp[i] = g_global.env_copy[i];
		i++;
	}
	tmp[i++] = ft_strdup(v);
	tmp[i] = NULL;
	g_global.env_copy = tmp;
}

int	var_parser(char *v)
{
	int	i;

	i = 0;
	while (v[i] && v[i] != '=')
	{
		if ((ft_isalpha(v[i]) || ft_isdigit(v[i]) || v[i] == '_')
			&& ft_isdigit(v[0]) == 0)
			i++;
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(v, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (g_global.exited = 1, 1);
		}
	}
	if (v[0] == '=')
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(v, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (g_global.exited = 1, 1);
	}
	copying_2(v);
	return (1);
}

int	check_variable(char *var)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (var[len] && var[len] != '=')
		len++;
	while (g_global.env_copy[i])
	{
		if (ft_ncmp(g_global.env_copy[i], var, len + 1) == 0)
		{
			g_global.env_copy[i] = ft_strdup(var);
			return (1);
		}
		else if (ft_ncmp(g_global.env_copy[i], var, len) == 0 && var[len
				+ 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

// void    copying(t_g_global *g_global)
// {
//     int i;

//     i = 0;
//     while (g_global->env_copy[i])
//         i++;
//     g_global->export = malloc((i + 1) * sizeof(char *));
//     i = 0;
//     while (g_global->env_copy[i])
//     {
//         g_global->export[i] = ft_strdup(g_global->env_copy[i]);
//         i++;
//     }
// }

int	export_listing(char **cmd)
{
	int	len;

	len = 0;
	if (!cmd[1])
	{
		while (g_global.env_copy[len])
			len++;
		sort_list(len);
		len = 0;
		while (g_global.env_copy[len])
		{
			printf("declare -x ");
			putstr(g_global.env_copy[len]);
			len++;
		}
		return (1);
	}
	return (0);
}

int	export(char **cmd)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	if (export_listing(cmd))
		return (ft_exited(1, 0));
	while (cmd[i])
	{
		j = 0;
		if (check_variable(cmd[i]))
			j = 1;
		if (j != 1)
		{
			var_parser(cmd[i]);
		}
		i++;
	}
	return (0);
}
