/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 16:22:23 by tsoares-          #+#    #+#             */
/*   Updated: 2024/10/16 17:46:37 by tsoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int execute_builtins(t_node *token, t_env *env)
{
	int	i;
	int	count;
	char	**args;
	t_node	*arg_token;

	// DEBUG
	if (!token || !token->value)
	//{
		//printf("execute_builtins.c --> Erro: token é NULL!!!\n");
		//return (0);
	//}
	return (0);
	//if (token->value == NULL)
	//{
		//printf("execute_builtins.c --> Erro: token->value é NULL!!!\n");
		//return (0);
	//}
	//else
		//printf("execute_builtins.c --> token->next->value: %s\n", token->next->value);
	//printf("execute_builtins.c --> Comando: %s\n", token->value);

	//if (env == NULL)
	//{
		//printf("execute_builtins.c --> Erro: env é NULL!!!\n");
		//return (-1);
	//}
	//else
		//printf("execute_builtins.c --> env válido!!!\n");


	if (ft_strncmp(token->value, "cd", 2) == 0)
	{
		//printf("Executando cd:\n"); // DEBUG
		/*if (token->next)
			return (cd(token->next->value, env)); // Se cd tiver argumento, passa o próximo token como argumento do cd
		else
			return (cd(NULL, env));*/
		if (token->next)
		{
			//printf("Argumento do cd: %s\n", token->next->value); // DEBUG
			return (cd(token->next->value, env));
		}
		else
		{
			//printf("cd não tem argumento\n"); // DEBUG
			return (cd(NULL, env));
		}
    }
    else if (ft_strncmp(token->value, "echo", 4) == 0)
//		return (echo(&token->next->value)); // Passar os argumentos do echo
	{
		//DEBUG
		//printf("Executando echo:\n");
		if (!token->next)
		{
			//printf("builtins: echo --> echo não tem argumento | token->next é NULL\n");
			return (echo(NULL));
		}

		// contar o nº de argumentos
		arg_token = token->next;// Se echo tiver argumento, printar ele(s)
		count = 0;
		//printf("Argumentos do echo: "); // DEBUG
		while (arg_token)
		{
			//printf("%s ", arg_token->value); // DEBUG
			count++;
			arg_token = arg_token->next;
		}

		// criar um array de strings para passar para o echo
		args = (char **)malloc(sizeof(char *) * (count + 1)); // +1 pro NULL do final
		if (!args)
		{
			//printf("execute_builtins.c --> echo\n"); // DEBUG
			perror("Error: memory allocation failure!\n");
			return (0);
		}
		arg_token = token->next; // voltar p/o 1º argumento e depois copiar os args p/o array
		i = 0;

		// preencher o array de argumentos;
		while (arg_token)
		{
			if (!arg_token->value)
			{
				free(args); // se der erro, dar free
				//printf("execute_builtins --> Erro: arg_token->value é NULL\n");
				return (0);
			}

			//printf("builtins: echo --> arg_token->value: %s\n", arg_token->value);
			args[i] = arg_token->value; // copiar o valor do token p/o array de args
			//printf("builtins: echo --> Array args[%d]: %s\n", i, args[i]); // DEBUG
			i++;
			arg_token = arg_token->next;
		}
		args[i] = NULL;

		// chamar echo c/o array de argumentos
		i = echo(args);
		free(args);
		//printf("\n");
		return (i);

//		if (token->next != NULL && token->next->value == NULL)
//		{
//			printf("token->next || token->next->value é NULL\n");
//			return (-1);
//		}

//		return (echo(&token->next->value));
	}
   	/*else if (ft_strncmp(token->value, "exit", 4) == 0)
    	{
        	builtin_exit();
        	return (1);
    	}*/
    else if (ft_strncmp(token->value, "pwd", 3) == 0)
		return (pwd());
	return (-1); // Se não for built-in, retornar -1
}
