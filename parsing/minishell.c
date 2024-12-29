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
        //     if (input->left)
        //         printf("left %d\n", input->left->tok);
        //     if (input->right)
        //         printf("right %d\n", input->right->tok);
        //     exit(0);
        //     // printf("%d\n", input->redirections->tok );

        //     // fprintf(stderr ,"1 -> %d\n", input->redirections->tok);
            
        //     // fprintf(stderr ,"2 -> %d\n", input->redirections->right->tok);
        //     printf("-------------------\n");
        //     // exit(0);
        // }
            // eprintf("%d\n", input->redirections->right->tok);
        
        ft_execute(input);
        global.executed = 0;
    }
	return 0;
}
