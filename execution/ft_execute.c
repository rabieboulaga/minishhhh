/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:16:20 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 23:44:11 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	should_expnd(int *flg)
{
	if (flg)
		*flg = 0;
}

int	calc_len(char *s)
{
	int			l;
	int			save;
	char		keep;
	static int	i = 0;

	l = 0;
	while (*s)
	{
		if (*s == 34 || *s == 39)
		{
			keep = *s;
			save = check_next_quote(s, keep);
			if (save == -1)
				return (-1);
			s += save + 1;
			l += save;
		}
		else
		{
			s++;
			l++;
		}
	}
	i++;
	return (l);
}

char	*new_cmd(char *s, int *flg)
{
	char	*new;
	int		l;
	char	keep;

	new = (char *)ft_malloc(sizeof(char) * (calc_len(s) + 1));
	if (!new)
	{
		printf("failes\n");
		exit(1);
	}
	l = 0;
	while (*s)
	{
		if (*s == 34 || *s == 39)
		{
			keep = *s++;
			should_expnd(flg);
			while (*s != keep)
				new[l++] = *s++;
			s++;
			continue ;
		}
		new[l++] = *s++;
	}
	return (new[l] = '\0', new);
}

void	delete_quotes(char **args)
{
	char	*str;

	while (*args)
	{
		str = new_cmd(*args, NULL);
		if (!str)
			return ;
		*args = str;
		args++;
	}
}

char	**parsing_cmd(char *str)
{
	int		len;
	char	*cmd;
	int		i;
	char	**return_cmd;

	len = 0;
	i = 0;
	len = find_len(str);
	if (len < 0)
		return (NULL);
	cmd = (char *)ft_malloc(sizeof(char) * (len + 1));
	if (!cmd)
		return (NULL);
	return_cmd = fill_command(str, len, &i, 0);
	delete_quotes(return_cmd);
	return (return_cmd);
}
