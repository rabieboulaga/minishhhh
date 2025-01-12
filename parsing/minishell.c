/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 21:22:43 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 23:33:07 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_g_global	g_global;

t_garbage	*ft_lstnew_garbage(void *ptr)
{
	t_garbage	*new_node;

	new_node = malloc(sizeof(t_garbage));
	if (!new_node)
		return (NULL);
	new_node->ptr = ptr;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back_garbage(t_garbage **lst, t_garbage *new)
{
	t_garbage	*current;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	free_garbage(void)
{
	t_garbage	*current;
	t_garbage	*tmp;

	current = g_global.garbage;
	while (current)
	{
		tmp = current;
		if (current->ptr)
			free(current->ptr);
		current = current->next;
		free(tmp);
	}
	g_global.garbage = NULL;
}

void	*ft_malloc(int size)
{
	void	*str;

	str = malloc(size);
	if (!str)
		return (NULL);
	ft_lstadd_back_garbage(&(g_global.garbage), ft_lstnew_garbage(str));
	return (str);
}

int	main(int argc, char **argv, char **env)
{
	char	*rl;
	int		fd_input;
	int		fd_output;
	t_input	*input;

	(void)argc;
	(void)argv;
	ft_initialize(env, &fd_input, &fd_output);
	while (1)
	{
		handle_signals(BEFORE_READLINE);
		rl = readline("minishell --> ");
		handle_signals(IN_PARENT);
		if (!rl)
			break ;
		g_global.executed = 1;
		add_history(rl);
		input = ft_parse(rl);
		expand_real(input);
		ft_execute(input);
		g_global.executed = 0;
	}
	free_garbage();
	rl_clear_history();
	return (0);
}
