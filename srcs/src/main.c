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
        printf("arg: %s\n", av[i]);
        if (av[i][0] == '-') {
            bool_t skip = u_getopts(av, i, opts);
            i = (skip) ? i + 1 : i;
        } else {
            if (url == NULL) {
                url = av[i];
            }
        }
        i++;
    }
    if (opts->help == 1)
    {
        free(opts);
        return (u_help());
    } else if (url == NULL) {
        u_printerr("usage error", "Destination address required");
    } else if (opts->max_hops == 1) {
        u_printerr("usage error", "<max_hops> should be bigger than 1");
    } else {
        return (
            e_start(url, opts)
        );
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
