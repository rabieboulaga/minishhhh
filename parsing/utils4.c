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
	printf("syntax error: unclosed quotes\n");
	return (-1);
}

void	check_flag(int flag, char *s, int *k)
{
	if (!flag)
		s[(*k) - 1] = 127;
}

int	check_true(s_token tok)
{
	if (tok == STR || tok == IN || tok == OUT || tok == APPEND
		|| tok == HEREDOC)
		return (1);
	else
		return (0);
}

int	build_redir_list(s_redir **head, s_redir *add)
{
	s_redir	*plus;

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
