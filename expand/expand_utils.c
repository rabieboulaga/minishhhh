/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:39:59 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 22:40:00 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	handle_env_var(char **word, int i)
{
	int		len;
	char	*var_name;
	char	*var_value;
	char	*new_word;

	len = 1;
	while ((*word)[i + len] && (ft_isalnum((*word)[i + len]) || (*word)[i
			+ len] == '_'))
		len++;
	var_name = ft_substr(*word, i + 1, len - 1);
	if (!var_name)
		return (1);
	var_value = get_env_value(var_name);
	if (!var_value)
		return (1);
	new_word = replace_substring(*word, i, len, var_value);
	if (!new_word)
		return (1);
	*word = new_word;
	return (len);
}

int	handle_dollar_sign(char **word, int i, char quote)
{
	if ((*word)[i + 1] == '?')
		return (handle_exit_status(word, i));
	else if ((*word)[i + 1] >= '0' && (*word)[i + 1] <= '9')
		return (handle_numeric(word, i));
	else if (is_legit((*word)[i + 1]) && quote != '\'')
		return (handle_env_var(word, i));
	return (1);
}

char	get_quote_state(char c, char curr_quote)
{
	if ((c == '"' || c == '\'') && curr_quote == 0)
		return (c);
	else if (c == curr_quote)
		return (0);
	return (curr_quote);
}

char	*process_word(char *word)
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
			i += handle_dollar_sign(&result, i, quote);
		else
			i++;
	}
	return (result);
}

char	*join_words(char **words)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (words[i])
	{
		result = ft_strjoin(result, words[i]);
		if (words[i + 1])
		{
			result = ft_strjoin(result, " ");
		}
		i++;
	}
	return (result);
}
