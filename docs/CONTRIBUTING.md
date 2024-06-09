# Contributing Rules



## Introduction

This document outlines the rules and procedures for contributing to the minishell project. Our aim is to maintain a clear, organized, and efficient workflow to ensure high-quality code and a smooth develop process. We are adopting some Scrum ceremonies and a hybrid Gitflow-TBD (Trunk-Based Development) workflow to manage our development tasks.



## Scrum Ceremonies

Each sprint will last two weeks and will include the following ceremonies:



1. **Planning + Backlog Refinement** (Monday, Day 1):
   
   * **Objective**: Define and refine the tasks for the upcoming sprint, creating a clear and actionable backlog.
   
   * **Output**: A detailed backlog of tasks for the new sprint.
     
     

2. **Weekly** (Saturday, Day 6):  >>>>>>>> include Code Review, ask cohort 1 cadets help when needed
   
   * **Objective**: Asses the progress of the sprint, discuss any blockers, and adjust the plan if necessary.
   
   * **Output**: Updated sprint plans and resolution for any impediments.
     
     

3. **Review** (Wednesday, Day 10):
   
   * **Objective**: Review the completed tasks, demonstrate the new features and gather feedback. 
   
   * **Output**: Approved features and feedback for future improvements.
     
     

4. **Retrospective** (Saturday, Day 13):
   
   * **Objective**: Reflect on the sprint, identify what went well, what didn't, and plan for improvements.
   
   * **Output**: Actionable insights for process improvements.
     
     

### Ceremony Schedule

| Day    | Ceremony                      | Description                                    |
| ------ | ----------------------------- | ---------------------------------------------- |
| Day 1  | Planning + Backlog Refinement | Define and refine tasks, generate backlog      |
| Day 6  | Weekly                        | Asses progress, discuss blockers, adjust plans |
| Day 7  | Rest                          | Rest Day                                       |
| Day 10 | Review                        | Review completed tasks, gather feedback        |
| Day 13 | Retrospective                 | Reflect on the sprint, identify improvements   |
| Day 14 | Rest                          | Rest day                                       |





## Pull Request (PR) Validation

- Process:
  
  - Tasks moving to PR will transition from `In Progress` to `validation`in GitHub Projects.
  
  - PR validations will be conducted in meetings where each developer presents their work.
  
  - Tests will be executed and validated by the other team memberto approve the PR.
    
    
    
    

## Documentation

A dedicated section in the README will link to our study documentation, providing resources and inghts relevant to our development process.





## Hybrid Gitflow-TBD Workflow

> RESUME GITFLOW and TBD here and why addopting hybrid workflow management



#### Branch structure

| Name             | Purpose                                                  | Merge                                                              | Naming Convention        |
| ---------------- | -------------------------------------------------------- | ------------------------------------------------------------------ | ------------------------ |
| Main             | Contains stable code ready for submission (production)   | Only from `develop`when the project version is stable and complete | -------                  |
| Develop          | Main branch for continous development                    | From feature branches when functionalities are complete            | -------                  |
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
   
   - The appoval mus make sure  that `main`branch is up to date (`git pull`command);
   
   - Merge the `develop` 

5. **Bug Fixes**:







[Markdown® Avançado: Sintaxe, Uso &amp; Exemplos [Passo a Passo]](https://markdown.net.br/sintaxe-estendida/)
