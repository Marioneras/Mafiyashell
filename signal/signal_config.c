#include "minishell.h"

volatile sig_atomic_t g_signal = 0;
//c'est un fichier de configuration
//ces fontions initialisent et configurent les signaux et reririgent daans les cas voulu

// MARION ATTENTION NOTION IMPORTANTE : Une nouvelle configuration ECRASE l'ancienne
// chaque ronction a un type de configiration pour SIQUINT=ctrl C et SIGINT=ctrl"\"
// c'est pour ca qu'on reconfigure des qu on change parmis les 3 cas, cela permet
// de changer le comportement en fonciton de ce qu'on veut faire !

void    normal_signal(void) //doit etre appeller dans la loop principal
{
    struct sigaction sa; //structure qui contient la config
    sa.sa_handler = handle_normal_sigint; // antenne
    sigemptyset(&sa.sa_mask); //vide la blacklist (antenne a l ecoute de tout signal)
    sa.sa_flags = SA_RESTART; //redemmarre appell syrsteme
    sigaction(SIGINT, &sa, NULL); //config SIGINT

    signal(SIGQUIT, SIG_IGN); // en gros ingore ctrl "\"
}

void    in_exec_signal(void)// doit etre appelle pendant l execution d'une cmd
{
    struct sigaction sa; //struction qui contient la config
    sa.sa_handler = handle_exec_sigint; // antenne
    sigemptyset(&sa.sa_mask); //vide la blacklist (antenne a l ecoute de tout signal)
    sigaddset(&sa.sa_mask, SIGCHLD);
    sa.sa_flags = SA_RESTART; //redemmarre apl syrsteme
    sigaction(SIGINT, &sa, NULL); //config SIGINT
    signal(SIGCHLD, handle_sigchld);
    signal(SIGQUIT, handle_sigquit); 
}

//celle la pour gerer dans le sprocess child child
void    child_signal(void) //doit etre appeller dans le process fils (apres le fork)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}
// en gros SIG_DFL permet de copier le comportement par defaut du systeme (pour ctrl C et \)

