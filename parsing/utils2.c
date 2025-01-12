/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:54:51 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 23:33:07 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	handle_interrupt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_global.exited = 130;
}

int	choose_str(char c, int flag)
{
	if ((flag && return_token(c, 0) == STR) || (!flag && return_token(c,
				0) == STR && !check_spaces(c)))
		return (1);
	else
		return (0);
}

int	str_len(char *s, int i, int flag)
{
	int	l;
	int	keep;

	l = 0;
	while (s[i] && choose_str(s[i], flag))
	{
		if (s[i] == 34 || s[i] == 39)
		{
			keep = check_next_quote(&s[i + 1], s[i]);
			if (keep == -1)
				return (-1);
			l += keep + 1;
			i += keep + 1;
		}
		l++;
		i++;
	}
	if (!flag)
	{
		while (check_spaces(s[i++]))
			l++;
	}
	return (l);
}

void	incre(char *s, int *i)
{
	ssize_t	l;

	l = str_len(s, *i, 1);
	while (l--)
		(*i)++;
}

s_redir	*node_create_redirection(char **s, s_token tok)
{
	s_redir	*node;

	if (!s)
		return (NULL);
	node = (s_redir *)ft_malloc(sizeof(s_redir));
	if (!node)
	{
		printf("failes\n");
		exit(1);
	}
	node->tok = tok;
	node->file = s[0];
	node->flag = 1;
	node->fd = -1;
	node->left = NULL;
	node->right = NULL;
	s = NULL;
	return (node);
}
