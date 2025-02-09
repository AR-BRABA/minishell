/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:03:03 by tsoares-          #+#    #+#             */
/*   Updated: 2025/02/08 21:57:12 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* returns $ position if found outside simple quote. else: -1 */
int	strdol(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == '$')
			if (str[i + 1] == '?' || (is_name(str[i + 1]) && !ft_isdigit(str[i
							+ 1])))
				return (i);
		i++;
	}
	return (-1);
}

int	decide_expansion(char *str, int dol, char *tmp)
{
	int	i;
	int	squote;
	int	dquote;
	int	expansion;

	i = 0;
	squote = 2;
	dquote = 2;
	expansion = &str[dol] - tmp;
	while (tmp && tmp[i] && i <= expansion)
	{
		if (tmp[i] == '\"' && squote % 2 == 0)
			dquote++;
		if (tmp[i] == '\'' && dquote % 2 == 0)
			squote++;
		else if (tmp[i] == '$')
			if ((squote % 2 == 0 && dquote % 2 == 0) || (dquote % 2 != 0
					&& squote % 2 == 0))
				if (tmp[i + 1] == '?' || (is_name(tmp[i + 1])
						&& !ft_isdigit(tmp[i + 1])))
					return (i);
		i++;
	}
	return (-1);
}

char	*expand_variable(char *expanded, char *str, t_env *env)
{
	char	*tmp;
	int		dol;
	int		varlen;
	char	*var;
	char	*value;

	tmp = str;
	dol = strdol(str);
	while (str && dol >= 0 && decide_expansion(str, dol, tmp) >= 0)
	{
		var = str + dol;
		varlen = strlen_isname(var);
		expanded = ft_strnjoin(expanded, str, (var - str));
		if (g_tecno_status != -24)
			value = ft_itoa(g_tecno_status);
		else
			value = get_variable_value(env, var, varlen);
		if (value)
			expanded = ft_strfjoin(expanded, value);
		if (g_tecno_status != -24)
			free(value);
		str += (var - str) + varlen;
		dol = strdol(str);
	}
	return (ft_strfjoin(expanded, str));
}

void	expand(t_node *token, t_env *env)
{
	char	*expanded;

	expanded = expand_variable(NULL, token->value, env);
	free(token->value);
	token->value = expanded;
}
