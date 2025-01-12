/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shuinting_yard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:25:09 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 21:25:12 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	the_organizer(t_input **input, t_input **tok_stack,
		t_input **new_stack)
{
	while (*input)
	{
		if ((*input)->tok == STR)
			push(input, new_stack, 0);
		else if ((*input)->tok != LPR && (*input)->tok != RPR)
		{
			while (*tok_stack
				&& (*tok_stack)->token_flag >= (*input)->token_flag)
				push(tok_stack, new_stack, 0);
			push(input, tok_stack, 1);
		}
		else if ((*input)->tok == LPR)
			push(input, tok_stack, 1);
		else if ((*input)->tok == RPR)
		{
			remove_top(input);
			while ((*tok_stack)->tok != LPR)
				push(tok_stack, new_stack, 0);
			remove_top(tok_stack);
		}
	}
}

t_input	*organizer(t_input **input)
{
	t_input	*tok_stack;
	t_input	*new_stack;

	tok_stack = NULL;
	new_stack = NULL;
	the_organizer(input, &tok_stack, &new_stack);
	while (tok_stack)
		push(&tok_stack, &new_stack, 0);
	return (new_stack);
}

void	push(t_input **a_input, t_input **b_input, int flag)
{
	t_input	*sep;

	if (!a_input || !(*a_input))
		return ;
	sep = *a_input;
	*a_input = (*a_input)->right;
	sep->right = NULL;
	if (*a_input)
		(*a_input)->left = NULL;
	if (flag == 1)
		push_2(b_input, sep);
	else
		build_command_list(b_input, sep);
}

void	push_2(t_input **top, t_input *to_add)
{
	if (!to_add)
		return ;
	else if (!*top)
		*top = to_add;
	else
	{
		(*top)->left = to_add;
		to_add->right = *top;
		*top = to_add;
	}
}

void	remove_top(t_input **tok_s)
{
	if (!(*tok_s)->right)
		*tok_s = NULL;
	else
	{
		*tok_s = (*tok_s)->right;
		(*tok_s)->left = NULL;
	}
}
