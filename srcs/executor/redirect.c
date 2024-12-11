#include "../../includes/minishell.h"

// testcases not working:
// << delimiter1 << delimiter2
// << del > file
void	redirect(t_list *cmdlist)
{
	int	fd[2];
	t_node *token= cmdlist->head;
	char *input;

	// loop para percorrer a cmdlist
	while (token != NULL)
	{
		// <
		if (token->type == REDIRECT_IN)
		{
			// verificar se arquivo existe & se temos permissao de leitura
			// if (access(token->next->value, 0)) ?

			// abre o arquivo e guarda no fd[0]
			fd[0] = open(token->next->value, O_RDONLY);
			// se nao houve nenhum erro no fd, dupa e substitui o std in 
			if (fd[0] < 0 || dup2(fd[0], 0) < 0)
			{
				// resolver mensagem
				perror("minishell");
				// ft_error("", token->next->value, " );
				exit(1);
			}
			// fechamos o fd gerado pelo open pois nao sera mais usado
			close(fd[0]);
			// token->next eh o arquivo/argumento do redirect,
			// entao vamos para token->next->next para continuar checando redirects
			token = token->next->next;
		}
		else if (token->type == HEREDOC) // testar
		{
			// usamos um pipe para redirecionar o texto de input do heredoc
			pipe(fd);
			// guardamos a saida da readline
			input = readline("> ");
			// enquanto nao achar o delimitador do heredoc (token->next->value) no input, continua guardando os inputs
			while (ft_strncmp(input, token->next->value, ft_strlen(token->next->value) + 1) != 0) 
			{
				// escrevemos diretamente no fd[1] -> fd de escrita, como se ele estivesse lendo com a readline
				write(fd[1], input, ft_strlen(input));
				write(fd[1], "\n", 1);
				free(input);
				input = readline("> ");
			}
			if (fd[0] < 0 || dup2(fd[0], 0) < 0)
			{
				perror("minishell");
				exit(1);
			}
			close(fd[0]);
			close(fd[1]);
			token = token->next->next;
		}
		else if (token->type == REDIRECT_OUT || token->type == APPEND)
		{
			if (token->type == APPEND)
				fd[1] = open(token->next->value, O_CREAT | O_RDWR, 0664); // append nao apaga o que tem no arquivo, so concatena
			else
				fd[1] = open(token->next->value, O_CREAT | O_TRUNC | O_RDWR, 0664);
			// se nao houver arquivo, cria. se houver conteudo, apaga. 0664 -> permissoes padroes de arquivos criados
			if (fd[1] < 0 || dup2(fd[1], 1) < 0)
			{
				perror("minishell");
				exit(1);
			}
			close(fd[1]);
			token = token->next->next;
		}
		else
			token = token->next; // se n for redirect, vai pro prox node
	}
}

