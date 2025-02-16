/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:30:57 by rabie             #+#    #+#             */
/*   Updated: 2025/01/11 23:17:34 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_ncmp(const char *str1, const char *str2, int n)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (i < n && (str1[i] != '\0'))
	{
		if (str1[i] != str2[i])
			return (1);
		i++;
	}
	return (0);
}
