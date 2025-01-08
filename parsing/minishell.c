#include "../headers/minishell.h"

s_global global; 
 
static void	sig_handler(int signum)
{
    (void)signum;
    if(!global.executed)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
        global.exited = 1;
    }
}

void handle_signal()
{
    rl_catch_signals = 0;
    if(signal(SIGINT, sig_handler) == SIG_ERR
        || signal(SIGQUIT, SIG_IGN) == SIG_ERR
		|| signal(SIGTSTP, SIG_IGN) == SIG_ERR)
        global.exited = 1;
}

void default_signal()
{
    if(signal(SIGINT, sig_handler) == SIG_ERR
        || signal(SIGQUIT, SIG_DFL) == SIG_ERR
		|| signal(SIGTSTP, SIG_DFL) == SIG_ERR)
    {
        global.exited = 1;
    }
}

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
        // printf("1-  %d\n", global.executed);
        handle_signal();
        rl = readline("minishell --> ");
        if(!rl)
        {
            break;
        }
        global.executed = 1;
        add_history(rl);
        input = ft_parse(rl);
        expand_real(input);
        ft_execute(input);
        global.executed = 0;
        // printf("2-  %d\n", global.executed);
    }
	return 0;
}
