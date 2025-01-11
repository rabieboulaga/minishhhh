/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_herdoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:18:55 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 23:33:07 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_strjoin_three(char *s1, char *s2, char *s3)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(s1, s2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, s3);
	return (result);
}

int	handle_exit_status(char **word, int i)
{
	char	*exit_str;
	char	*new_word;
	char	*before;
	char	*after;

	exit_str = ft_itoa(g_global.exited);
	if (!exit_str)
		return (1);
	before = ft_substr(*word, 0, i);
	after = ft_strdup(*word + i + 2);
	if (!before || !after)
		return (1);
	new_word = ft_strjoin_three(before, exit_str, after);
	*word = new_word;
	return (1);
}

char	*replace_substring(char *str, int start, int len, char *new_str)
{
	char	*before;
	char	*after;
	char	*result;

	before = ft_substr(str, 0, start);
	after = ft_strdup(str + start + len);
	if (!before || !after)
		return (NULL);
	result = ft_strjoin_three(before, new_str, after);
	return (result);
}

char	*process_word_herdoc(char *word)
{
	int		i;
	char	quote;
	char	*result;

	i = 0;
	quote = 0;
	result = ft_strdup(word);
	if (!result)
		return (NULL);
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1] == '$')
		{
			while (result[i + 1] == '$')
			{
				result++;
			}
		}
		quote = get_quote_state(result[i], quote);
		if (result[i] == '$')
			i += handle_dollar_sign(&result, i, 0);
		else
			i++;
	}
	return (result);
}

char	*check_expand_herdoc(char *input)
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
		words[i] = process_word_herdoc(words[i]);
		i++;
	}
	result = join_words(words);
	return (result);
}
