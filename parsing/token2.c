/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:28:07 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 21:28:09 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_syntax(s_token tok, char *s)
{
	s_token	check;

	check = return_token(*s, *(s + 1));
	if (check_syntax_help(tok, check) == 1)
		return (1);
	if (check == END)
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
	else if (check == AND || check == OR || check == APPEND || check == HEREDOC)
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putchar_fd(*(s + 1), 2);
		ft_putchar_fd(*(s + 1), 2);
		ft_putstr_fd("'\n", 2);
	}
	else
	{
		ft_putstr_fd("bash: syntax error near unexpected token `", 2);
		ft_putchar_fd(*s, 2);
		ft_putstr_fd("'\n", 2);
	}
	g_global.exited = 2;
	return (0);
}

char	*cmd_help(char *s, int l, int *k, int flag)
{
	int		i;
	int		j;
	char	*ret;

	ret = (char *)ft_malloc(sizeof(char) * (l + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < l)
	{
		if (s[*k] == 34 || s[*k] == 39)
		{
			j = check_next_quote(&s[(*k) + 1], s[*k]) + i + 1;
			while (i < j)
			{
				ret[i++] = s[(*k)++];
				check_flag(flag, s, k);
			}
		}
		if (s[*k] == 32)
			s[*k] = 127;
		ret[i++] = s[(*k)++];
		check_flag(flag, s, k);
	}
	return (ret[i] = 0, ret);
}

char	**prep_cmd(char *s, int *i, int flag, s_token tok)
{
	char	**freturn;

	s[*i] = 127;
	(*i)++;
	if (tok == HEREDOC || tok == APPEND)
	{
		s[*i] = 127;
		(*i)++;
	}
	while (check_spaces(s[*i]) == 1)
		(*i)++;
	if (check_syntax(tok, (s + *i)) == 0)
		return (NULL);
	freturn = fill_command(s, str_len(s, *i, flag), i, flag);
	return (freturn);
}

char	*ft_substr_len(char *s, int *i, int save)
{
	char	*str;

	save = str_len(s, *i, 1);
	if (save < 0)
		return (NULL);
	str = ft_substr(s, *i, save);
	if (!str)
		return (NULL);
	return (str);
}

s_input	*token_2(char *s, int *i, s_token tok)
{
	int		save;
	char	*str;
	s_redir	*redir;

	save = *i;
	redir = NULL;
	while (check_true(tok) == 1)
	{
		if (tok != STR)
		{
			if (!build_redir_list(&redir, node_create_redirection(prep_cmd(s,
							&save, 0, tok), tok)))
				return (0);
		}
		else
			save++;
		if (s[save] == '\0')
			tok = return_token(s[save], 'x');
		else
			tok = return_token(s[save], s[save + 1]);
	}
	str = ft_substr_len(s, i, 1);
	if (!str)
		return (NULL);
	return (incre(s, i), node_creation_cmd(str, redir, STR, 0));
}
