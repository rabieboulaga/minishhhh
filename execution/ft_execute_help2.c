/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_help2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 23:44:40 by rboulaga          #+#    #+#             */
/*   Updated: 2025/01/11 23:44:41 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	expand(t_input *input)
{
	input->cmd = parsing_cmd(input->command);
	if (!input->cmd)
		return (0);
	input->command = NULL;
	return (1);
}

int	is_legit(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

char	*ft_getenv(char *s)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = ft_strlen(s);
	while (g_global.env_copy[i] && j > 0)
	{
		if (ft_strncmp(s, g_global.env_copy[i], j + 1) == -61)
		{
			output = ft_strdup(&g_global.env_copy[i][j + 1]);
			if (!output)
			{
				return (NULL);
			}
			return (output);
		}
		i++;
	}
	return (NULL);
}

int	find_len(char *str)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == 39)
			ret += look_for_1_quote(str, &i, str[i]);
		else if (str[i] == 34)
			ret += look_for_1_quote(str, &i, str[i]);
		else
		{
			i++;
			ret++;
		}
	}
	return (ret);
}

int	look_for_1_quote(char *str, int *i, char c)
{
	int	ret;

	ret = 0;
	while (str[*i])
	{
		(*i)++;
		ret++;
		if (str[*i] == c)
		{
			(*i)++;
			ret++;
			return (ret);
		}
	}
	return (-1);
}
