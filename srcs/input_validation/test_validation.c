#include "../../includes/minishell.h"

void    run_test_cases(char *cases[], bool (*test_func)(char *), bool expected_result, const char *test_type)
{
    int     i;
    bool    result;

    i = 0;
    printf("\n%s:\n", test_type);
    while (cases[i])
    {
        result = test_func(cases[i]);
        if (result == expected_result)
            printf("minishell$ %s   --->>>   pass!\n", cases[i]);
        else
            printf("minishell$ %s   --->>>   FAILED\n", cases[i]);
        i++;
    }
}

void    test_check_pipe_redirect_sequences()
{
    char    *valid_cases[] = {"<<", ">>", "|>", "|   >", "|<", "|   <", "|<<", "|   <<", "|>>", "|   >>", NULL};
    char    *invalid_cases[] = {
        "<   <", ">   >", "|<  <", "|   <   <", "|>  >", "|   >  >", "|>>>", "|    >>>",
        "|> >>", "|> > >", "| > >>", "| > > >", "|<<<", "|   <<<", "|< <<", "|< < <", "|<< <", "| < <<", "| << <",
        "| < < <", ">|", "> |", "<|", "<   |", ">>|", "> >|", ">>   |", "> > |", "<<|", "< <|", "<<   |", "< < |",
        "||", "|   |", "|||", "| ||", "|| |", "| | |", NULL
        };
    
    printf("\n======= TESTING: check_pipe_redirect_sequences =======\n\n");
    run_test_cases(valid_cases, check_pipe_redirect_sequences, true, "CASOS VÁLIDOS");
    run_test_cases(invalid_cases, check_pipe_redirect_sequences, false, "CASOS INVÁLIDOS");
    printf("\n======================================================\n\n");
}

int main(void)
{
    test_check_pipe_redirect_sequences();

    
    return (0);
}