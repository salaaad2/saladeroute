/*********************************/
/*   FT_TRACEROUTE          (  //      */
/*   main              ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "u_libft.h"
#include "u_opts.h"
#include "u_helper.h"

#include "traceroute.h"

int
main(int ac, char *av[])
{
    char * url;
    t_opts * opts;
    int i;
    int status;

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
            status = u_getopts(av, i, opts);
            if (status == -1)
            {
                u_printerr("usage error", av[i]);
                return (1);
            } else if (status == 1) {
                i += 1;
            }
        } else {
            if (url == NULL) {
                url = av[i];
            }
        }
        i++;
    }
    if (opts->help == 1)
    {
        u_help();
    } else if (url == NULL) {
        u_printerr("usage error", "Destination address required");
    } else if (opts->max_hops <= 1) {
        u_printerr("usage error", "<max_hops> should be bigger than 1");
    } else if (opts->nqueries > 10) {
        u_printerr("usage error", "<nqueries> should be smaller than 10");
    } else if (opts->seq > 10) {
        u_printerr("usage error", "<seq> should be smaller than 10");
    } else {
        e_start(url, opts);
    }
    free(opts);
    return (0);
}

/*
** ====== INFO ======
** Files prefixes info
** -------------------
** no prefix: main
** p_  -> packets
** u_  -> utils
*/
