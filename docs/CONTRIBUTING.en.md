# Contributing Rules



## Introduction

This document outlines the rules and procedures for contributing to the minishell project. Our aim is to maintain a clear, organized, and efficient workflow to ensure high-quality code and a smooth develop process. We are adopting some Scrum ceremonies and a hybrid Gitflow-TBD (Trunk-Based Development) workflow to manage our development tasks.



## Scrum Ceremonies

Each sprint will last two weeks and will include the following ceremonies:



1. **Planning + Backlog Refinement** (Monday, Day 1):
   
   * **Objective**: Define and refine the tasks for the upcoming sprint, creating a clear and actionable backlog.
   
   * **Output**: A detailed backlog of tasks for the new sprint.
     
     

2. **Weekly** (Saturday, Day 6): 
   
   * **Objective**: Code review, asses the progress of the sprint, discuss any blockers, and adjust the plan if necessary.
   
   * **Output**: Updated sprint plans and resolution for any impediments.
     
     

3. **Weekly** (Wednesday, Day 10):
   
   * **Objective**: Asses the progress of the sprint, discuss any blockers, and adjust the plan if necessary.
   
   * **Output**: Updated sprint plans and resolution for any impediments.
     
     

3. **Review** (Saturday, Day 13):
   
   * **Objective**: Review the completed tasks, demonstrate the new features and gather feedback. 
   
   * **Output**: Approved features and feedback for future improvements.
     
     

4. **Retrospective** (Saturday, Day 13):
   
   * **Objective**: Reflect on the sprint, identify what went well, what didn't, and plan for improvements.
   
   * **Output**: Actionable insights for process improvements.
     
     

### Ceremony Schedule

| Day    | Ceremony                      | Description                                                                              |
| ------ | ----------------------------- | ---------------------------------------------------------------------------------------- |
| Day 1  | Planning + Backlog Refinement | Define and refine tasks, generate backlog                                                |
| Day 6  | Weekly                        | Code review, asses sprint progress, discuss blockers, adjust plans                       |
| Day 7  | Rest                          | Rest Day                                                                                 |
| Day 10 | Weekly                        | Asses progress, discuss blockers, adjust plans                                           |
| Day 13 | Review + Retrospective        | Review completed tasks, gather feedback.<br>Reflect on the sprint, identify improvements |
| Day 14 | Rest                          | Rest day                                                                                 |





## Pull Request (PR) Validation

- Process:
  
  - Tasks moving to PR will transition from `In Progress` to `Validation` in **minishell**'s' GitHub Projects;
  
  - PR validations will be conducted in meetings where each developer presents their work;
  
  - Tests will be executed and validated by the other team member to approve the PR.
    
    
    
    

## Documentation

A dedicated section in the README will link to our study documentation, providing resources and inghts relevant to our development process.





## Simplified Gitflow-TBD Approach

#### Introduction

Our project's small scale and limited functionality initially led us to consider adopting Trunk-Based Development (TBD). However, concerns about code instability and the challenge of identifying issues raised red flags. Additionally, frequent commits - while essencial - can be dauting, especially for those less accustomed to them.



#### The Hybrid Approach

To strike a balance, we adopted a hybrid model that combines the best of both worlds: Gitflow and TBD. Here's why it makes sense:

1. **Organized structure**: Gitflow provides clear organization. We'll have `main` (for stable code) and `develop` (for continuous development), ensuring stability while avoiding excessive branches.

2. **Simplicity**: TBD's continuous integration and simpler implementation align with our goals. Frequent merges into `develop` keep us agile.
   
   

#### Benefits

- **Efficiency**: We'll avoid Gitflow's branch complexity while benefiting from continuous integration.

- **Learning focus**: The hybrid approach let us concentrate on development and learning without overwhelming branch management.
  
  

#### Branch structure

| Name             | Purpose                                                  | Merge                                                              | Naming Convention        |
| ---------------- | -------------------------------------------------------- | ------------------------------------------------------------------ | ------------------------ |
| Main             | Contains stable code ready for submission (production)   | Only from `develop`when the project version is stable and complete | `main`                   |
| Develop          | Main branch for continous development                    | From feature branches when functionalities are complete            | `develop`                |
| Feature Branches | Temporary branches for developing specif functionalities | Into `develop`once the feature is complete and tested              | `feature/<feature-name>` |



#### Workflow steps

1. **Creating a Feature Branch**:
   
   - Start from the `develop`branch;
   
   - Pull the latest changes (`git pull`command);
   
   - Create a new branch using  the naming convention `feature/<feature-name>`.
     
     

2. **Development and Testing**:
   
   - Develop the functionality on the specific feature branch;
   
   - Perform thorough testing  to ensure quality.
     
     

3. **Merging into `develop`**:
   
   - Make sure to be in the `develop`branch;
   
   - Ensure the `develop`branch is up to date (`git pull`command);
   
   - Merge the temporary feature branch into `develop`.
     
     

4. **Merging `develop`into `main`**:
   
   - Create a pull request (PR);
   
   - The PR must be reviewed, tested and approved by the other team member;
   
   - The approval must ensure to be in `main`branch;
   
   - The approval must make sure  that `main` branch is up to date (`git pull`command);
   
   - Merge the `develop` .
     
     

5. **Bug Fixes**:
   
   - Ensure your local repository is up to date (`git pull` command);
   
   - Start from the `develop`branch;
   
   - Create a new branch using the name convention `fix/<describe-bug-concisely>`;
   
   - Merge the temporary feature branch into `develop`;
   
   - Follow "**Merging `develop` into `main`**" (#4) steps.
     
     

#### Conclusion

By blending Gitflow's structure with TDB's simplicity, we can achieve stability, agility, and a strong focus on learning and development.



    **Resources list**:

- [Markdown® Avançado: Sintaxe, Uso &amp; Exemplos [Passo a Passo]](https://markdown.net.br/sintaxe-estendida/);
- [markdown-guide/_basic-syntax/line-breaks.md at master · mattcone/markdown-guide · GitHub](https://github.com/mattcone/markdown-guide/blob/master/_basic-syntax/line-breaks.md);
- [Saiba tudo sobre o Gitflow Workflow | Atlassian Git Tutorial](https://www.atlassian.com/br/git/tutorials/comparing-workflows/gitflow-workflow#:~:text=O%20que%20%C3%A9%20Gitflow%3F,por%20Vincent%20Driessen%20no%20nvie);
- [Trunk-Based Development vs. GitFlow: Which Source Code Control is Right for You? | Splunk](https://www.splunk.com/en_us/blog/learn/trunk-based-development-vs-gitflow.html);
- [Trunk Based Development vs Gitflow | by Tim Mutton | Medium](https://medium.com/@hellotimmutton/trunk-based-development-vs-gitflow-aada37103c7a);
- [Trunk-Based Development vs Git Flow: When to Use Which Development Style (mergify.com)](https://blog.mergify.com/trunk-based-development-vs-git-flow-when-to-use-which-development-style/);
- [Naming conventions for Git Branches - a Cheatsheet](https://medium.com/@abhay.pixolo/naming-conventions-for-git-branches-a-cheatsheet-8549feca2534#:~:text=Hotfix%20Branches%3A%20These%20branches%20are,for%20a%20new%20production%20release.);
- [What is a Code Review &amp; How It Can Save Time | Atlassian](https://www.atlassian.com/agile/software-development/code-reviews);
- [git pull | Atlassian Git Tutorial](https://www.atlassian.com/br/git/tutorials/syncing/git-pull);
- [Como fazer o seu primeiro pull request no GitHub](https://www.freecodecamp.org/portuguese/news/como-fazer-o-seu-primeiro-pull-request-no-github/);
- [GitHub - jonatasemidio/multilanguage-readme-pattern: Just another way to enable more than one language in our readme files](https://github.com/jonatasemidio/multilanguage-readme-pattern);
- [Four agile ceremonies, demystified | Atlassian](https://www.atlassian.com/agile/scrum/ceremonies);
- [The 5 Scrum Ceremonies Explained for Remote Teams | Parabol](https://www.parabol.co/blog/scrum-ceremonies-for-remote-teams/);
- [What is a Code Review &amp; How It Can Save Time | Atlassian](https://www.atlassian.com/agile/software-development/code-reviews).
