/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:18:47 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 23:33:07 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

void	expand_real(s_input *input)
{
	if (!input)
		return ;
	if (input->tok == STR)
		input->command = check_expand(input->command);
	expand_real(input->left);
	expand_real(input->right);
}

int	handle_numeric(char **word, int i)
{
	char	*new_word;

	new_word = ft_strdup(*word + i + 2);
	if (!new_word)
		return (1);
	*word = new_word;
	return (2);
}

char	*get_env_value_help(char *value, char *save)
{
	int	j;

	j = 0;
	while (*value != '\0')
	{
		if (ft_isspace(*value) == 1)
			save[j] = *value;
		else if (ft_isspace(*value) == 0)
		{
			save[j] = ' ';
			while (ft_isspace(*value) == 0)
				value++;
		}
		j++;
		value++;
	}
	return (save[j] = '\0', save);
}

char	*get_env_value(char *name)
{
	int		i;
	char	*value;
	char	*save;

	i = 0;
	while (g_global.env_copy[i])
	{
		if (!ft_strncmp(name, g_global.env_copy[i], ft_strlen(name))
			&& g_global.env_copy[i][ft_strlen(name)] == '=')
		{
			value = ft_strdup(ft_strchr(g_global.env_copy[i], '=') + 1);
			save = (char *)ft_malloc(ft_strlen_no_space(value) + 1);
			save = get_env_value_help(value, save);
			return (save);
		}
		i++;
	}
	return (ft_strdup(""));
}

char	*check_expand(char *input)
{
	char	**words;
	char	*result;
	int		i;

	words = ft_split(input, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		words[i] = process_word(words[i]);
		i++;
	}
	result = join_words(words);
	return (result);
}
