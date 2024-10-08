/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtnins.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:22:23 by tsoares-          #+#    #+#             */
/*   Updated: 2024/09/27 17:01:03 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int execute_builtins(t_node *token)
{
    /*if (strcmp(token->value, "cd") == 0)
    {
        builtin_cd(token->next);
        return (1);
    }
    else if (strcmp(token->value, "echo") == 0)
    {
        builtin_echo(token->next);
        return (1);
    }
    else if (strcmp(token->value, "env") == 0)
    {
        builtin_env();
        return (1);
    }
    else if (strcmp(token->value, "export") == 0)
    {
        builtin_export(token->next);
        return (1);
    }
    else if (strcmp(token->value, "exit") == 0)
    {
        builtin_exit();
        return (1);
    }
    else if (strcmp(token->value, "pwd") == 0)
    {
        builtin_pwd();
        return (1);
    }
    else if (strcmp(token->value, "unset") == 0)
    {
        builtin_unset(token->next);
        return (1);
    }
    return (0); // Se não for built-in, retornar 0
    */

   // só pra testar execute_external_commands()
   (void)token;
   return (-1);
}

