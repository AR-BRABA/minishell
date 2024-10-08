/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_external_commands.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:02:18 by tsoares-          #+#    #+#             */
/*   Updated: 2024/10/27 20:32:26 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

void execute_external_command(t_node *token)
{
    pid_t pid;
    char *exec_args[1024];  // Array para armazenar os argumentos
    int i = 0;
    t_node *arg_token;

    pid = fork();  // Criar processo filho p/ executar comando externo
    if (pid == 0)  // tô no processo filho
    {
        // formatar os tokens em um array de argumentos
        arg_token = token;
        while (arg_token != NULL)
        {
            exec_args[i] = arg_token->value;  // preencher cada argumento
            arg_token = arg_token->next;
            i++;
        }
        exec_args[i] = NULL;

        // executar comando externo com execvp
        if (execvp(exec_args[0], exec_args) == -1)
        {
            perror("execvp failed");
            exit(1);  // sair do processo filho
        }
    }
    else if (pid > 0)  // tô no processo pai
        wait(NULL);  // esperar processo filho terminar
    else
        perror("fork failed");
}
