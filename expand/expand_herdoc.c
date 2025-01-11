#include "../headers/minishell.h"


// char **ft_split_diff(char *s, char c)
// {
//     int i = 0;
//     char *str;
//     int save = 0;
//     char **tt;
//     int j = 0;


//     while (s[i])
//     {
//         if (s[i] == '$' && s[0] != '$')
//         {
//             str = ft_substr(s, 0, i);
//             tt = ft_split(s, 39);
//             while(tt[j])
//             {
//                 if(j == 0)
//                     tt[0] = ft_strdup(str);
//                 else
//                     tt[j] = ft_strjoin("$", tt[j]);
//                 j++;
//             }
//             break ;
//         }
//         else if (s[0] == '$')
//         {
//             tt = ft_split(s, '$');
//             while(tt[j])
//             {
//                 tt[j] = ft_strjoin("$", tt[j]);
//                 j++;
//             }
//             break ;
//         }
//         i++;
//     }
//     j = 0;
//     return(tt);
// }


// size_t	ft_strlen_diff(const char *s)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s[i] && s[i] != 39)
// 		i++;
// 	return (i);
// }

// char *ft_getenv(char *s)
// {
//     int i;
//     int j;
//     char *str;
//     char **spp;
//     int l = 0;
//     i = 0;

//     str = ft_strdup("");
//     spp = ft_split_diff(s, '$');
//     while(spp[l])
//     {
//         j = ft_strlen_diff(spp[l]);

//         if(j>0)
//         {
//             while(global.env_copy[i] && spp[l][0] == '$')
//             {
//                 if(spp[l][0] == '$' && ft_strncmp(&spp[l][1], global.env_copy[i], j-1) == 0)
//                 {
//                     spp[l] = ft_strdup(ft_strchr(global.env_copy[i], '=') + 1);
//                     if (!spp[l])
//                     {
//                         return NULL;
//                     }
//                 }
//                 i++;
//             }
//             if(spp[l][0] == '$')
//             {
//                 spp[l] = ft_strdup("");
//             }
//         }
        
//         i = 0;
//         str = ft_strjoin(str,spp[l]);
//         l++;
//     }
//     l = 0;
//     return str;
// }


// char *check_expand(s_input *input)
// {
//     char *str;
//     int i = 0;
//     char *return_str;
//     char **work;
//     int j = 0;

//     return_str = ft_strdup("");
//     work = ft_split(input->command, ' ');
//     while(work[j])
//     {  
//         while(work[j][i])
//         {
//             if(work[j][i] == '$' && work[j][i+1] == '?')
//             {
//                 work[j] = ft_strdup(ft_itoa(global.exited));
//             }
//             else if(work[j][i] == '$' && is_legit(work[j][i+1])==1)
//             {
//                 if(work[j][i+1] >= '0' && work[j][i+1] <= '9')
//                 {
//                     i++;
//                     i++;
//                     work[j] = ft_strdup(&work[j][i]);
//                 }
//                 else
//                 {
//                     str = ft_getenv(work[j]);
//                     work[j] = ft_strdup(str);
//                 }
//             }
//             else if(work[j][i] == '$' && (work[j][i+1] == 34 || work[j][i+1] == 39)
//             || work[j][i] == '$' && work[j][i+1] == '$')
//             {
//                 i++;
//                 while(work[j][i] == '$')
//                 {
//                     i++;
//                 }
//                 work[j] = ft_strdup(&work[j][i]);
//             }
//             i++;
//         }
//         return_str = ft_strjoin(return_str,work[j]);
//         return_str = ft_strjoin(return_str, " ");
//         i = 0;
//         j++;
//     }
//     return return_str;
// }


// char	*ft_strjoin_three(char *s1, char *s2, char *s3)
// {
// 	char	*temp;
// 	char	*result;

// 	temp = ft_strjoin(s1, s2);
// 	if (!temp)
// 		return (NULL);
// 	result = ft_strjoin(temp, s3);
// 	return (result);
// }

static char	*replace_substring(char *str, int start, int len, char *new_str)
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

static int	handle_exit_status(char **word, int i)
{
	char	*exit_str;
	char	*new_word;
	char	*before;
	char	*after;

	// printf("exited  %d\n", global.exited);
	exit_str = ft_itoa(global.exited);
	if (!exit_str)
		return (1);
	before = ft_substr(*word, 0, i);
	after = ft_strdup(*word + i + 2);
	if (!before || !after)
		return (1);
	new_word = ft_strjoin_three(before, exit_str, after);
	*word = new_word;
	return (2);
}

static int	handle_numeric(char **word, int i)
{
	char	*new_word;

	new_word = ft_strdup(*word + i + 2);
	if (!new_word)
		return (1);
	*word = new_word;
	return (2);
}

// static char	*get_env_value(char *name)
// {
// 	int		i;
// 	char	*value;

// 	i = 0;
// 	while (global.env_copy[i])
// 	{
// 		if (!ft_strncmp(name, global.env_copy[i], ft_strlen(name)) &&
// 			global.env_copy[i][ft_strlen(name)] == '=')
// 		{
// 			value = ft_strdup(ft_strchr(global.env_copy[i], '=') + 1);
// 			return (value);
// 		}
// 		i++;
// 	}
// 	return (ft_strdup(""));
// }

static int	handle_env_var(char **word, int i)
{
	int		len;
	char	*var_name;
	char	*var_value;
	char	*new_word;

	len = 1;
	while ((*word)[i + len] && (ft_isalnum((*word)[i + len]) ||
			(*word)[i + len] == '_'))
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

static int	handle_dollar_sign(char **word, int i, char quote)
{
	if ((*word)[i + 1] == '?')
	{
		// printf("the ? entery\n");
		return (handle_exit_status(word, i));
	}
	else if ((*word)[i + 1] >= '0' && (*word)[i + 1] <= '9')
	{
		// printf("num enetery\n");
		return (handle_numeric(word, i));
	}
	else if (is_legit((*word)[i + 1]) && quote != '\'')
	{
		// printf("the  ccc is %c --> \n", (*word)[i + 1]);
		return (handle_env_var(word, i));
	}
	return (1);
}

static char	get_quote_state(char c, char curr_quote)
{
	if ((c == '"' || c == '\'') && curr_quote == 0)
		return (c);
	else if (c == curr_quote)
		return (0);
	return (curr_quote);
}

static char	*process_word_herdoc(char *word)
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
		if(result[i] == '$' && result[i + 1] == '$')
		{
			while(result[i+1] == '$')
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

static char	*join_words(char **words)
{
	int		i;
	char	*result;
	// char	*temp;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (words[i])
	{
		// temp = result;
		result = ft_strjoin(result, words[i]);
		if (words[i + 1])
		{
			// temp = result;
			result = ft_strjoin(result, " ");
		}
		i++;
	}
	return (result);
}

char	*check_expand_herdoc(char *input)
{
	char	**words;
	char	*result;
	// char	*temp;
	int		i;

	words = ft_split(input, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		// temp = words[i];
		words[i] = process_word_herdoc(words[i]);
		i++;
	}
	result = join_words(words);
	return (result);
}