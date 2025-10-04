
#include "minishell.h"

//en gros ce fichier contient les focntion qui sont utiliser par les appels de siganaux
// une fonction dans le cas du prompt normal, une autre si on execute une commande

extern volatile sig_atomic_t g_signal;//permet de stocker le dernier signal recu

//cella la pour le prompt
void    handle_normal_sigint(int sig)
{
    g_signal = sig;                 // Sauvegarde le signal
    write(1, "\n", 1);             // Affiche nouvelle ligne
    rl_replace_line("", 0);        // Efface la ligne courante
    rl_on_new_line();              // Se positionne sur nouvelle ligne
    rl_redisplay();                // Réaffiche le prompt
}

//celle quand on execute une cmd
void    handle_exec_sigint(int sig)
{
    g_signal = sig;             // Sauvegarde le signal
    write(1, "\n", 1);
    rl_replace_line("", 0);        // Efface la ligne courante
    rl_on_new_line();              // Se positionne sur nouvelle ligne
    // Pas de rl_redisplay() : on ne veut pas réafficher le prompt
}

void	handle_heredoc_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
	unlink(".heredoc");
}

void    handle_sigquit(int sig) // = ctrl backslash
{
    write(STDERR_FILENO, "Quit (core dumped)\n", 19);  // Message standard
    g_signal = sig;
   // rl_replace_line("", 0);        // Efface la ligne courante
   // rl_on_new_line();              // Se positionne sur nouvelle ligne                  // Évite le warning "unused parameter"
}

void handle_sigchld(int sig)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
        g_signal = sig;
}
