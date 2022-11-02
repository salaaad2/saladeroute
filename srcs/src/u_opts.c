/*********************************/
/*   FT_TRACEROUTE     (  //      */
/*   opts              ( )/      */
/*   by salade         )(/       */
/*  ________________  ( /)       */
/* ()__)____________)))))   :^}  */
/*********************************/

#include <stdlib.h>
#include <stdio.h>
#include "u_opts.h"

t_opts *
u_initopts( void ) {
    t_opts * ret = (t_opts*)malloc(sizeof(t_opts));

    if (ret != NULL) {
        ret->nqueries = 3;
        ret->max_hops = 30;
        ret->seq = -1;
        ret->verbose = 0;
        ret->help = 0;
        ret->textaddr = 0;
    }
    return (ret);
}

int
u_getopts(char *av[], int index, t_opts *opts) {
    int opt_hops, opt_nqueries, opt_seq;
    char *s;
    char c;

    s = av[index];
    c = s[1];
    switch (c) {
        case 'v':
            opts->verbose = TRUE;
            break;
        case 'h':
            opts->help = TRUE;
            break;
        case 'm':
            if (av[index + 1] != NULL)
            {
                opt_hops = atoi(av[index + 1]);
                if (opt_hops != 0)
                {
                    opts->max_hops = opt_hops;
                }
            }
            break;
        case 'q':
            if (av[index + 1] != NULL)
            {
                opt_nqueries = atoi(av[index + 1]);
                if (opt_nqueries != 0)
                {
                    opts->nqueries = opt_nqueries;
                }
            }
            break;
        case 'p':
            if (av[index + 1] != NULL)
            {
                opt_seq = atoi(av[index + 1]);
                if (opt_seq != 0)
                {
                    opts->seq = opt_seq;
                }
            }
            break;
    }
    return (0);
}
