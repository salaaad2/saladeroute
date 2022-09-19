/*********************************/
/*   FT_PING          (  //      */
/*   main              ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include <stdlib.h>
#include <unistd.h>

#include "u_libft.h"

#include "p_main.h"
#include "u_opts.h"
#include "u_err.h"
#include "u_helper.h"
#include "e_ping.h"

/*
** check for flags;
** initialize linked list containing t_elem elements with all non option arguments.
** ^ this was dumb and subsequently got removed
*/

int main(int ac, char *av[])
{
    char * url;
    t_opts * opts;
    int i;

    if (getuid() != 0)
    {
        return (
            u_printerr("fatal error", "insuficient rights")
        );
    }

    url = NULL;
    i = 1;
    opts = u_initopts();
    while (i < ac)
    {
        if (av[i][0] == '-') {
            u_getopts(av, opts);
        } else {
            if (url == NULL) {
                url = av[i];
            } else {
                return (
                    u_printerr("usage error", "Destination address required")
                    );
            }
        }
        i++;
    }
    if (opts->help == 1)
    {
        return (u_help());
    } else if (url == NULL) {
        return (
            u_printerr("usage error", "Destination address required")
            );
    } else {
        return (
            e_start(url, opts)
        );
    }
    return (0);
}

/*
** ====== INFO ======
** Files prefixes info
** -------------------
** p_  -> packets
** e_  -> exec
** u_  -> utils
*/
