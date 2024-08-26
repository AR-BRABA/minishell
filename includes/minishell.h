/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:11:33 by tsoares-          #+#    #+#             */
/*   Updated: 2024/08/26 19:07:13 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct	s_envnode {
	char	*key;
	char	*value;
	struct s_envnode	*prev;
	struct s_envnode	*next;
} t_envnode;

typedef struct	s_env {
	int	len;
	t_envnode	*head;
	t_envnode	*tail;
} t_env;

char	*read_input(char *user_input);
bool	validate_input(char *input);

// ENV.C
t_envnode	*new_envnode(char *envp);
void	addback_env(t_envnode *newnode, t_env *list);
t_env	*get_env_list(char **envp);
void	print_env(t_env	*env);

#endif
