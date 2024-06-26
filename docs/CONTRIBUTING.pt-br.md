# Regras de contribuição



## Introdução

Este documento descreve as regras e os procedimentos para contribuir com o projeto minishell. Nosso objetivo é manter um fluxo de trabalho claro, organizado e eficiente para garantir código de alta qualidade e um processo de desenvolvimento tranquilo. Adotamos algumas cerimônias Scrum e um fluxo de trabalho híbrido Gitflow-TBD (Trunk-Based Development) para gerenciar nossas tarefas de desenvolvimento.

<br><br>

## Cerimônias do Scrum

Cada sprint terá duração de duas semanas e incluirá as seguintes cerimônias:



1. **Planjejamento + Refinamento do Backlog** (segunda-feira, dia 1):
   
   * **Objetivo**: Definir e refinar as tarefas para a próxima sprint, criando um backlog claro e implementável.
   
   * **Resultado**: Um backlog detalhado de tarefas para a nova sprint.
     
     <br>

2. **Weekly** (sábado, dia 6):
   
   - **Objetivo**: Revisão de código, avaliar o progresso da sprint, discussão sobre impedimentos e ajuste do planejamento, se necessário.
   * **Resultado**: Atualização do planejamento da sprint e solução de impedimentos.
     
     <br>

3. **Weekly** (quarta-feira, dia 10):
   
   - **Objetivo**: Avaliar o progresso da sprint, discussão sobre impedimentos e ajuste do planejamento, se necessário.
   * **Resultado**: Atualização do planejamento da sprint e solução de impedimentos.
     
     <br>

4. **Review** (sábado, dia 13):
   
   * **Objetivo**: Revisar as tarefas concluídas, demonstrar as novas funcionalidades e obter feedbacks.
   
   * **Resultado**: Aprovação das novas funcionalidades implementadas e feedback para melhorias futuras.
     
     <br>

5. **Retrospectiva** (Saturday, Day 13):
   
   * **Objetivo**: Refletir sobre a sprint, identificar os acertos, o que não deu certo e planejar melhorias.
   
   * **Resultado**: Insights práticos para aprimoramento de processos.
   
   <br>

### Quadro de Cerimônias

| Dia    | Cerimônia                             | Descrição                                                                                      |
| ------ | ------------------------------------- | ---------------------------------------------------------------------------------------------- |
| Day 1  | Planejamento + Refinamento do Backlog | Definir e refinar as tarefas, gerar backlog                                                    |
| Day 6  | Weekly                                | Revisão de código, avaliar progresso, discussão de impedimentos, ajustar planejamento          |
| Day 7  | Folga                                 | Dia de descanso                                                                                |
| Day 10 | Weekly                                | Avaliar progresso, discussão de impedimentos, ajustar planejamento                             |
| Day 13 | Review + Retrospectiva                | Revisar tarefas concluídas, obter feedbacks.<br>Refletir sobre a sprint, identificar melhorias |
| Day 14 | Folga                                 | Dia de descanso                                                                                |

<br>

<br>

## Validação de Pull Request (PR)

* Processo:
  
  * As tarefas em PR passarão de `In Progress` para `Validation` no GitHub Projects do projeto **minishell**;
  
  * As validações de PR serão realizadas em reuniões onde cada desenvolvedora apresentará seu trabalho;
  
  * Os testes serão executados e validados pelo outro membro da equipe para aprovar o PR.
    <br><br>

## Documentação

Uma seção dedicada no README irá linkar nossa documentação de estudo, fornecendo recursos e insights relevantes para nosso processo de desenvolvimento.

<br><br>

## Fluxo de trabalho: Abordagem híbrida Gitflow-TBD

#### Introdução

A pequena escala de nosso projeto e pouca quantidade de funcionalidades nos levaram inicialmente a considerar a adoção do Desenvolvimento Baseado em Tronco (TBD). Mas nossas preocupações com a instabilidade do código e a dificuldade de identificar problemas, nos geraram alertas. Além disso, os frequentes commits - embora essenciais - podem ser desafiadores, especialmente para aqueles que não estão acostumados.

<br>

#### A abordagem híbrida

Para encontrar um equilíbrio, adotamos um modelo híbrido que combina o melhor dos dois mundos: Gitflow e TBD. Aqui está o porquê:

1. **Estrutura organizada**: O Gitflow oferece uma organização clara. Teremos `main` (para código estável) e `develop` (para desenvolvimento contínuo), garantindo estabilidade e evitando ramificações excessivas.

2. **Simplicidade**: A integração contínua e a implementação mais simples do TBD estão alinhadas com nossos objetivos. Os merges frequentes na `develop` nos mantêm ágeis.
   
   <br>

#### Benefícios

- **Eficiência**: Evitaremos a complexidade de ramificações do Gitflow e nos beneficiaremos da integração contínua do TBD.
* **Foco no aprendizado**: A abordagem híbrida permite que nos concentremos no desenvolvimento e aprendizado sem sobrecarregar o gerenciamento de branches.
  <br><br>
  Branch structure
  
  | Name             | Purpose                                                                  | Merge                                                               | Naming Convention        |
  | ---------------- | ------------------------------------------------------------------------ | ------------------------------------------------------------------- | ------------------------ |
  | Main             | Contém o código estável pronto para avaliação (produção)                 | Apenas da `develop` quando a versão estiver estável e completa      | `main`                   |
  | Develop          | Branch principal para desenvolvimento contínuo                           | Das branches de funcionalidades quando estas estiverem completas    | `develop`                |
  | Feature Branches | Branches temporárias para desenvolvimento de funcionalidades específicas | Para a `develop` quando a funcionalidade estiver completa e testada | `feature/<feature-name>` |
  
  <br>
  
  #### Detalhamento do Fluxo de Trabalho
  
  1. **Criando uma Branch de Funcionalidade**:
     
     -  Certifique-se que está na branch *develop*:<br>
       `git branch`

     -  Se não está na *develop*, acesse-a:<br>
       `git switch develop`

     -  Atualize o repositório local:<br>
       `git pull`

     -  Crie uma nova branch usando a convenção de nomenclatura `feature/<nome-da-funcionalidade>`.
       <br>
       <br>
  2. **Desenvolvimento e Testes**:
     
     - Desenvolva a funcionalidade em sua branch específica;
     
     - Realize testes completos para garantir a qualidade.
       <br>
       <br>
  3. **Merge para a `develop`**:
     
     - Certifique-se que está na branch *develop*:<br>
      `git branch`

     - Se não está na *develop*, acesse-a:<br>
      `git switch develop`
     
     - Garanta que a branch *develop* esteja atualizada:
      `git pull`
     
     - Mescle a branch temporária da funcionalidade para a *develop*:
      `git merge <nome-da-branch>`

     - Ao finalizar o merge, delete a branch temporária
      `git branch -d <nome-da-branch>` 
       <br>
       <br>
  
  4. **Merge da `develop` para a `main`**:
     
     - Crie um pull request (PR);
  
     - Mova o card da tarefa da coluna `In progress` para a `Validation` no projeto **minishell** do Github Projects;
     
     - O PR deve ser revisado, testado e aprovado pelo outro membro da equipe;
     
     - A pessoa aprovadora deve garantir que está na branch *main*:<br>
      `git branch`
     
     - Se a pessoa aprovadora não estiver na *main*, deverá acessá-la:<br>
      `git switch main`

     - A pessoa aprovadora deve garantir que a branch *main* está atualizada:<br>
       `git pull`
     
     - Faça o merge da branch `develop` para a `main`:<br>
      git merge develop`
       <br>
       <br>
  5. **Correção de Bugs**:
     
     - Siga os passos da seção *#1* usando usando a convenção de nomenclatura `fix/<descrever-bug-de forma concisa>`;
     
     - Faça o merge da branch temporária de correção para a *develop*, seguindo as instruções das seções *#2* e *#3*;
     
     - Siga os passos da seção *#4*.
       
       <br>
  
  #### Conclusion
  
  Ao combinar a estrutura do Gitflow com a simplicidade do TDB, podemos alcançar estabilidade, agilidade e foco no aprendizado e desenvolvimento.
  <br><br>
  
  #### Fontes:
  
  * [Markdown® Avançado: Sintaxe, Uso &amp; Exemplos [Passo a Passo]](https://markdown.net.br/sintaxe-estendida/);
  * [markdown-guide/_basic-syntax/line-breaks.md at master · mattcone/markdown-guide · GitHub](https://github.com/mattcone/markdown-guide/blob/master/_basic-syntax/line-breaks.md);
  * [Saiba tudo sobre o Gitflow Workflow | Atlassian Git Tutorial](https://www.atlassian.com/br/git/tutorials/comparing-workflows/gitflow-workflow#:~:text=O%20que%20%C3%A9%20Gitflow%3F,por%20Vincent%20Driessen%20no%20nvie);
  * [Trunk-Based Development vs. GitFlow: Which Source Code Control is Right for You? | Splunk](https://www.splunk.com/en_us/blog/learn/trunk-based-development-vs-gitflow.html);
  * [Trunk Based Development vs Gitflow | by Tim Mutton | Medium](https://medium.com/@hellotimmutton/trunk-based-development-vs-gitflow-aada37103c7a);
  * [Trunk-Based Development vs Git Flow: When to Use Which Development Style (mergify.com)](https://blog.mergify.com/trunk-based-development-vs-git-flow-when-to-use-which-development-style/);
  * [Naming conventions for Git Branches - a Cheatsheet](https://medium.com/@abhay.pixolo/naming-conventions-for-git-branches-a-cheatsheet-8549feca2534#:~:text=Hotfix%20Branches%3A%20These%20branches%20are,for%20a%20new%20production%20release.);
  * [What is a Code Review &amp; How It Can Save Time | Atlassian](https://www.atlassian.com/agile/software-development/code-reviews);
  * [git pull | Atlassian Git Tutorial](https://www.atlassian.com/br/git/tutorials/syncing/git-pull);
  * [Como fazer o seu primeiro pull request no GitHub](https://www.freecodecamp.org/portuguese/news/como-fazer-o-seu-primeiro-pull-request-no-github/);
  * [GitHub - jonatasemidio/multilanguage-readme-pattern: Just another way to enable more than one language in our readme files](https://github.com/jonatasemidio/multilanguage-readme-pattern);
  * [Four agile ceremonies, demystified | Atlassian](https://www.atlassian.com/agile/scrum/ceremonies);
  * [The 5 Scrum Ceremonies Explained for Remote Teams | Parabol](https://www.parabol.co/blog/scrum-ceremonies-for-remote-teams/);
  * [What is a Code Review &amp; How It Can Save Time | Atlassian](https://www.atlassian.com/agile/software-development/code-reviews).
