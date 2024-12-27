#include "../headers/minishell.h"

s_global global;  


int main(int argc, char **argv, char **env)
{
    char *rl;
    int fd_input;
    int fd_output;
	(void)argc;
	(void)argv;
    int i = 0;
    s_input *input;

    ft_initialize(env, &fd_input, &fd_output); 
    while(1)
    {
        rl = readline("minishell --> ");
        if(!rl)
        {
            break;
        }
        global.executed = 1;
        add_history(rl);
        input = ft_parse(rl);
        // if (input->redirections != NULL)
        // {
        //     printf("%d\n", input->redirections->tok);
            
        //     printf("%d\n", input->redirections->right->tok);
        //     printf("-------------------\n");
        //     // exit(0);
        // }
            // eprintf("%d\n", input->redirections->right->tok);
        ft_execute(input);
        // sleep(100);
        global.executed = 0;
    }
    printf("dddddddddhere\n");

	return 0;
}
