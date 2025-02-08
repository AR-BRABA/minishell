/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 22:01:10 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 10:32:12 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* strlen while is a valid name for an enviroment variable ([a-z], [A-Z], '_',
		[0-9] except on index 0, '?') */
int	strlen_isname(char *str)
{
	int	i;

	i = 1;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '?')
		return (++i);
	while (str[i] && is_name(str[i]))
		i++;
	return (i);
}

/* returns index of the first quote found. if not found, returns -1 */
int	strquote(char *str, int start)
{
	int	i;

	i = start;
	while (str && str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (i);
		i++;
	}
	return (-1);
}

/* join s1 and s2 into return string until n bytes and free s1*/
char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*s;
	int		i;
	int		s_pos;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	s_pos = 0;
	s = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (s1 && s1[i] != '\0')
		s[i++] = s1[s_pos++];
	s_pos = 0;
	while (s2 && s2[s_pos] != '\0' && s_pos < n)
		s[i++] = s2[s_pos++];
	s[i] = '\0';
	free(s1);
	return (s);
}

/* join s1 and s2 into return string and free s1*/
char	*ft_strfjoin(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		s_pos;

	if (!s1 && !s2)
		return (NULL);
	s = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	i = 0;
	s_pos = 0;
	while (s1 && s1[i] != '\0')
		s[i++] = s1[s_pos++];
	s_pos = 0;
	while (s2 && s2[s_pos] != '\0')
		s[i++] = s2[s_pos++];
	s[i] = '\0';
	free(s1);
	return (s);
}

/* if not a heredoc delimiter, expands all variables that may exist. next,
	removes outside quotes that may exist */
void	format(t_tab *cmdtable, t_env *env)
{
	t_list	*cmd;
	t_node	*token;

	(void)env;
	cmd = cmdtable->head;
	token = cmd->head;
	if (!token)
		return ;
	while (cmd != NULL && token != NULL)
	{
		if (token->type != HEREDOC_DELIMITER)
			expand(token, env);
		rm_quote(token);
		token = token->next;
		if (token == NULL)
		{
			cmd = cmd->next;
			if (cmd == NULL)
				break ;
			token = cmd->head;
		}
	}
}
