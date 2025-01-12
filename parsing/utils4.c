/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:03:15 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 22:03:19 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_next_quote(char *s, char c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (*s)
	{
		if (*s == c)
			return (i);
		i++;
		s++;
	}
	return (-1);
}

void	check_flag(int flag, char *s, int *k)
{
	if (!flag)
		s[(*k) - 1] = 127;
}

int	check_true(t_token tok)
{
	if (tok == STR || tok == IN || tok == OUT || tok == APPEND
		|| tok == HEREDOC)
		return (1);
	else
		return (0);
}

int	build_redir_list(t_redir **head, t_redir *add)
{
	t_redir	*plus;

	if (!head || !add)
		return (0);
	if (!*head)
		*head = add;
	else
	{
		plus = *head;
		while (plus->right)
			plus = plus->right;
		plus->right = add;
		add->left = plus;
	}
	return (1);
}

char	**fill_command(char *s, int l, int *k, int flag)
{
	char	*prep;
	char	**freturn;

	if (l < 0)
		return (NULL);
	prep = cmd_help(s, l, k, flag);
	freturn = ft_split(prep, 127);
	prep = NULL;
	return (freturn);
}
