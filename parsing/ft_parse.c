/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:20:36 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 23:33:07 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	check_beggining(char *str)
{
	s_token	tok;

	if (str[0] == '\0')
		tok = return_token(str[0], 'x');
	else
		tok = return_token(str[0], str[1]);
	if (tok == OR || tok == AND)
	{
		printf("bash: syntax error near unexpected token %c%c'\n", str[0],
			str[1]);
		g_global.exited = 2;
		return (0);
	}
	else if (tok == PIPE || tok == RPR)
	{
		printf("bash: syntax error near unexpected token %c'\n", str[0]);
		g_global.exited = 2;
		return (0);
	}
	return (1);
}

s_input	*tokenizer(char *str)
{
	s_input	*input;
	int		parenthes;
	int		i;

	parenthes = 0;
	i = 0;
	input = NULL;
	while (str[i])
	{
		if (!token_1(&input, str, &i, &parenthes))
			return (NULL);
	}
	str = NULL;
	return (input);
}

int	handle_double_quotes(const char *str, int *i)
{
	(*i)++;
	while (str[*i])
	{
		if (str[*i] == '"')
			return (0);
		(*i)++;
	}
	return (1);
}

int	check_unclosed_quote(char *str)
{
	int	i;
	int	ret;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			ret = handle_double_quotes(str, &i);
			if (ret)
				return (ret);
		}
		else if (str[i] == '\'')
		{
			ret = handle_single_quotes(str, &i);
			if (ret)
				return (ret);
		}
		i++;
	}
	return (0);
}

s_input	*ft_parse(char *rl)
{
	char	*str;
	s_input	*input;

	if (check_unclosed_quote(rl))
	{
		ft_putstr_fd("unclosed quotes\n", 2);
		g_global.exited = 2;
		return (NULL);
	}
	str = ft_strtrim(rl, " \t\n\v\f\r");
	free(rl);
	if (!str || check_beggining(str) == 0)
	{
		return (NULL);
	}
	input = tokenizer(str);
	if (!input)
		return (NULL);
	input = shunting_yard(&input);
	while (input->right)
		input = input->right;
	input = list_to_tree(input);
	return (input);
}
