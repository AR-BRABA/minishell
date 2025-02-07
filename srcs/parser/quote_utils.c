/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:03:51 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/07 14:03:57 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* takes a quoted str as parameter and returns it's len without
 * outside quotes
 */
int	strlen_unquote(char *quotestr)
{
	int	i;
	int	start;
	int	quote;

	i = 0;
	start = 0;
	quote = 0;
	while (quotestr && quotestr[i] != '\0')
	{
		if (quotestr[i] == '\'' || quotestr[i] == '"')
		{
			quote++;
			start = i++;
			while (quotestr[i] && quotestr[i] != quotestr[start])
				i++;
			quote++;
		}
		i++;
	}
	return (i - quote);
}

void	build_unquoted(char *quoted, char *unquoted)
{
	int	squote;
	int	dquote;
	int	i;
	int	q;

	squote = 0;
	dquote = 0;
	i = 0;
	q = 0;
	while (quoted[i] != '\0')
	{
		if ((quoted[i] == '\'' && dquote % 2 == 0) || (quoted[i] == '\"'
				&& squote % 2 == 0))
		{
			if (quoted[i] == '\'')
				squote++;
			else
				dquote++;
			i++;
		}
		else
			unquoted[q++] = quoted[i++];
	}
	unquoted[q] = '\0';
}

/* tira aspas externas do token->value */
void	rm_quote(t_node *token)
{
	int		new_len;
	int		len;
	char	*unquoted;

	new_len = strlen_unquote(token->value);
	len = ft_strlen(token->value);
	if (len == new_len)
		return ;
	unquoted = malloc((len + 1) * sizeof(char));
	build_unquoted(token->value, unquoted);
	free(token->value);
	token->value = unquoted;
}
