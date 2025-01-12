/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:26:11 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 23:33:07 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_not_operator(t_token tok)
{
	if (tok == STR || tok == IN || tok == OUT || tok == APPEND
		|| tok == HEREDOC)
		return (1);
	else
		return (0);
}

int	check_rpr(char *s, int i)
{
	while (s[i] != '\0')
	{
		if (s[i] == ')')
			return (i);
		i++;
	}
	ft_putstr_fd("syntax error: unclosed parentheses\n", 2);
	g_global.exited = 2;
	return (-1);
}

int	check_spaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	else
		return (0);
}

int	check_syntax_help(t_token tok, t_token next)
{
	if (tok == OR || tok == AND || tok == PIPE)
	{
		if (next == STR || next == IN || next == OUT || next == APPEND
			|| next == LPR)
			return (1);
	}
	if (tok == LPR)
	{
		if (next == STR || next == IN || next == OUT || next == APPEND
			|| next == LPR)
			return (1);
	}
	if (tok == RPR)
	{
		if (next == AND || next == OR || next == PIPE || next == RPR
			|| next == END)
			return (1);
	}
	if (tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
	{
		if (next == STR)
			return (1);
	}
	return (0);
}

int	token_1(t_input **head, char *s, int *i, int *par)
{
	t_token	tok;
	t_input	*new;

	if (s[*i] == '\0')
		tok = return_token(s[*i], 'x');
	else
		tok = return_token(s[*i], s[(*i) + 1]);
	if (check_not_operator(tok) == 0)
	{
		if (return_token_syntax(tok, s, i, par) == 0)
			return (0);
		new = creat_node_command(NULL, NULL, tok, check_command(tok));
	}
	else
		new = token_2(s, i, tok);
	if (!new)
		return (0);
	if (new->tok == LPR)
	{
		if (new->tok == LPR)
			return (0);
	}
	build_command_list(head, new);
	return (1);
}
