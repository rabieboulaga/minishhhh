/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 01:15:00 by htemsama          #+#    #+#             */
/*   Updated: 2023/11/19 01:15:01 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*bullst;

	if (!new || !lst)
		return ;
	bullst = *lst;
	if (bullst)
	{
		while (bullst->next)
			bullst = bullst->next;
		bullst->next = new;
	}
	else
		*lst = new;
}
