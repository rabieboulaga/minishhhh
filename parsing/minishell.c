#include "../headers/minishell.h"

s_global global; 
 
// static void	sig_handler(int signum)
// {
//     if(signum == SIGINT && !global.executed)
//     {
//         write(1, "\n", 1);
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//         global.exited = 1;
//     }
//     else{
//             write(1, "\n", 1);
//             rl_on_new_line();
//             rl_replace_line("", 0);
//     }

// }

// static void	sig_handler_v1(int signum)
// {
//     if(signum == SIGQUIT && !global.executed)
//     {
//         write(1, "\n", 1);
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//         global.exited = 1;
//     }
//     else{
//             write(1, "QUIT\n", 5);
//             rl_on_new_line();
//             rl_replace_line("", 0);
//     }

// }


// void default_signal()
// {
//     rl_catch_signals = 0;
//     if(signal(SIGINT, sig_handler) == SIG_ERR
//         || signal(SIGQUIT, sig_handler_v1) == SIG_ERR
// 		|| signal(SIGTSTP, SIG_IGN) == SIG_ERR)
//         global.exited = 1;
// }

// void default_signal()
// {
//     if(signal(SIGINT, sig_handler) == SIG_ERR
//         || signal(SIGQUIT, sig_handler) == SIG_ERR
// 		|| signal(SIGTSTP, SIG_DFL) == SIG_ERR)
//     {
//         global.exited = 1;
//     }
// }

// static void	sig_handler(int signum)
// {
//     if(signum == SIGINT && !global.executed)
//     {
//         write(1, "\n", 1);
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//         global.exited = 1;
//     }
//     else{
//             write(1, "QUIT", 4);
//             rl_on_new_line();
//             rl_replace_line("", 0);
//     }

// }

// void handle_signal()
// {
//     rl_catch_signals = 0;
//     if(signal(SIGINT, sig_handler) == SIG_ERR
//         || signal(SIGQUIT, SIG_IGN) == SIG_ERR
// 		|| signal(SIGTSTP, SIG_IGN) == SIG_ERR)
//         global.exited = 1;
// }

// void default_signal()
// {
//     if(signal(SIGINT, sig_handler) == SIG_ERR
//         || signal(SIGQUIT, sig_handler) == SIG_ERR
// 		|| signal(SIGTSTP, SIG_DFL) == SIG_ERR)
//     {
//         global.exited = 1;
//     }
// }

static void	handle_interrupt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	global.status = 130;
}

static void	handle_heredoc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	global.status = 130;
	exit(130);
}

void	handle_signals(int sig)
{
	if (sig == IN_HEREDOC)
	{
		signal(SIGINT, handle_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == IN_CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (sig == IN_PARENT)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == BEFORE_READLINE)
	{
		signal(SIGINT, handle_interrupt);
		signal(SIGQUIT, SIG_IGN);
	}
}
void	sig_handler(int signum)
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

void handle_quit(int signum)
{
    // printf("---> %d and in_herdoc %d\n", global.executed, global.in_herdoc);
    (void)signum;
    if(!global.executed == 0)
    {
        // ft_putstr_fd("Quit (core dumped)\n", 2);
        signal(SIGQUIT, SIG_IGN);
    }
    if(global.executed == 1)
    {
        // printf("asdsadasdas");
        // printf("glooo is %d\n", global.in_herdoc);
        if(global.in_herdoc == 0)
        {
            // printf("QUIIII");
            ft_putstr_fd("Quit (core dumped)\n", 2);
        }
    }
}

// void handle_signal()
// {
//     rl_catch_signals = 0;
//     if(signal(SIGINT, sig_handler) == SIG_ERR
//         || signal(SIGQUIT, handle_quit) == SIG_ERR)
//         global.exited = 1;
// }
void default_signal()
{
    if(signal(SIGINT, sig_handler) == SIG_ERR
        || signal(SIGQUIT, handle_quit) == SIG_ERR)
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
    // int i = 0;  
    s_input *input;

    ft_initialize(env, &fd_input, &fd_output); 
    
    while(1)
    {
        // printf("1-  %d\n", global.executed);
        // printf("1-  %d\n", global.exited);
        // handle_signal();
        handle_signals(BEFORE_READLINE);
        rl = readline("minishell --> ");
        handle_signals(IN_PARENT);
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
        // printf("2-  %d\n", global.exited); 
    }
	return 0;
}

// int main()
// {
//     char *str = "      STR";
//     char **hello = ft_split(str, ' ');
//     printf("%s\n", hello[0]);
//     // printf("%s\n", str[1]);
// }