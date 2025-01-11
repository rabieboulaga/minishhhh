/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htemsama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 22:16:20 by htemsama          #+#    #+#             */
/*   Updated: 2025/01/11 22:16:22 by htemsama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	ft_execute(s_input *input)
{
	if (!input)
		return (8000);
	else
		check_heredoc(input);
	if (input->redirections)
	{
		redi_in(input);
	}
	else if (input->tok == AND)
		exec_and(input);
	else if (input->tok == OR)
		exec_or(input);
	else if (input->tok == PIPE)
		single_pipe(input);
	else if (input->tok == STR)
		return (exec_str(input));
	return (0);
}

void	exec_and(s_input *input)
{
	ft_execute(input->left);
	if (g_global.exited == 0)
		ft_execute(input->right);
}

void	exec_or(s_input *input)
{
	ft_execute(input->left);
	if (g_global.exited != 0)
		ft_execute(input->right);
}

void	fill_between_quote_1(char **str, char *s, int *i)
{
	while (s[*i])
	{
		*(*str)++ = s[(*i)++];
		if (s[*i] == 39)
		{
			*(*str)++ = s[(*i)++];
			*(*str) = '\0';
			return ;
		}
	}
}

int	exec_str(s_input *input)
{
	input->cmd = parsing_cmd(input->command);
	if (!input->cmd)
	{
		return (8000);
	}
	if (input->cmd && !input->cmd[0])
		(input->cmd = NULL);
	if (input->redirections != NULL)
	{
		if (input->redirections->fd != -1)
		{
			dup2(input->redirections->fd, STDIN_FILENO);
			close(input->redirections->fd);
			builtins(input->cmd);
			close(input->redirections->fd);
			return (8000);
		}
	}
	return (builtins(input->cmd));
}

int	expand(s_input *input)
{
	input->cmd = parsing_cmd(input->command);
	if (!input->cmd)
		return (0);
	input->command = NULL;
	return (1);
}

int	is_legit(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

char	*ft_getenv(char *s)
{
	int		i;
	int		j;
	char	*output;

	i = 0;
	j = ft_strlen(s);
	while (g_global.env_copy[i] && j > 0)
	{
		if (ft_strncmp(s, g_global.env_copy[i], j + 1) == -61)
		{
			output = ft_strdup(&g_global.env_copy[i][j + 1]);
			if (!output)
			{
				return (NULL);
			}
			return (output);
		}
		i++;
	}
	return (NULL);
}

int	find_len(char *str)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == 39)
			ret += look_for_1_quote(str, &i, str[i]);
		else if (str[i] == 34)
			ret += look_for_1_quote(str, &i, str[i]);
		else
		{
			i++;
			ret++;
		}
	}
	return (ret);
}

int	look_for_1_quote(char *str, int *i, char c)
{
	int	ret;

	ret = 0;
	while (str[*i])
	{
		(*i)++;
		ret++;
		if (str[*i] == c)
		{
			(*i)++;
			ret++;
			return (ret);
		}
	}
	return (-1);
}

void	should_expnd(int *flg)
{
	if (flg)
		*flg = 0;
}

int	calc_len(char *s)
{
	int			l;
	int			save;
	char		keep;
	static int	i = 0;

	l = 0;
	while (*s)
	{
		if (*s == 34 || *s == 39)
		{
			keep = *s;
			save = check_next_quote(s, keep);
			if (save == -1)
				return (-1);
			s += save + 1;
			l += save;
		}
		else
		{
			s++;
			l++;
		}
	}
	i++;
	return (l);
}

char	*new_cmd(char *s, int *flg)
{
	char	*new;
	int		l;
	char	keep;

	new = (char *)ft_malloc(sizeof(char) * (calc_len(s) + 1));
	if (!new)
	{
		printf("failes\n");
		exit(1);
	}
	l = 0;
	while (*s)
	{
		if (*s == 34 || *s == 39)
		{
			keep = *s++;
			should_expnd(flg);
			while (*s != keep)
				new[l++] = *s++;
			s++;
			continue ;
		}
		new[l++] = *s++;
	}
	return (new[l] = '\0', new);
}

void	delete_quotes(char **args)
{
	char	*str;

	while (*args)
	{
		str = new_cmd(*args, NULL);
		if (!str)
			return ;
		*args = str;
		args++;
	}
}

char	**parsing_cmd(char *str)
{
	int		len;
	char	*cmd;
	int		i;
	char	**return_cmd;

	len = 0;
	i = 0;
	len = find_len(str);
	if (len < 0)
		return (NULL);
	cmd = (char *)ft_malloc(sizeof(char) * (len + 1));
	if (!cmd)
		return (NULL);
	return_cmd = fill_command(str, len, &i, 0);
	delete_quotes(return_cmd);
	return (return_cmd);
}
